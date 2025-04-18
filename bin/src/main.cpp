#include <sg/buffer.h>
#include <sg/compression_zstd.h>

#include <H5Cpp.h>

#include <fstream>
#include <numeric>

// Un-commonet when running a GUI (to hide Windows terminal)
//
// #ifdef WIN32
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// #endif

int main(int, char **) {
    std::string group_name = "test_group";
    size_t group_size_hint = 1*(group_name.size()+2);


    H5::H5File file;
    {
        auto prop = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fapl_core(prop, 1000, 0);

        file = H5::H5File("test-image.hdf5", H5F_ACC_TRUNC, H5::FileCreatPropList::DEFAULT, prop);
        H5Pclose(prop);
    }

    {
        auto group = file.createGroup("test", group_size_hint);

        hsize_t legth = 10;
        auto    dataspace = H5::DataSpace(1, &legth);

        H5::IntType datatype(H5::PredType::NATIVE_INT);
        datatype.setOrder(H5T_ORDER_LE);

        std::vector<int> v(10);
        std::iota(v.begin(), v.end(), 1);

        auto dataset = group.createDataSet("test_channel", datatype, dataspace);
        dataset.write(v.data(), H5::PredType::NATIVE_INT);
    }

    file.flush(H5F_scope_t::H5F_SCOPE_GLOBAL);

    auto requiredSize =H5Fget_file_image(file.getId(), NULL, 0);
    auto buff = sg::make_unique_c_buffer<std::byte>(requiredSize);

    {
        if (H5Fget_file_image(file.getId(), buff.get(), buff.size()) <0)
            throw std::runtime_error("error saving file");
        file.close();
    }


    {
        std::ofstream of("image.hdf5");
        of.write((char*)buff.get(), buff.size());
    }

    {
        auto comp = sg::compression::zstd::compress(buff.get(), buff.size(), 3, 1);

        std::ofstream of("image.hdf5.zstd");
        of.write((char*)comp.get(), comp.size());
    }

    return 0;
}
