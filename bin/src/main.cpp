#include <iostream>
#include <sg/buffer.h>
#include <sg/compression_zstd.h>
#include <sg/random.h>

#include <H5Cpp.h>
#include "H5Zzstd.h"

#include <fstream>
#include <numeric>

// Un-commonet when running a GUI (to hide Windows terminal)
//
// #ifdef WIN32
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// #endif


int main(int, char **) {
    /* data */
    size_t length = 1E3;
    srand(1);
    std::vector<double> v(length);

    for (auto& val: v)
        val =1E4+ ((double) rand() / (RAND_MAX));

    //std::iota(v.begin(), v.end(), 1);
    int ch_count=10;

    /* compression */
    H5Zregister(H5Z_ZSTD);
    auto faplDataset = H5Pcreate(H5P_DATASET_CREATE);
    unsigned int comprression_level=3;
    hsize_t chunkSize=length;
    H5Pset_filter(faplDataset, H5Z_FILTER_ZSTD, H5Z_FLAG_MANDATORY, 1,  &comprression_level);
    H5Pset_layout(faplDataset, H5D_CHUNKED);
    H5Pset_chunk(faplDataset,1, &chunkSize);
    //H5Pset_shuffle(faplDataset);

    /* file image in memory */
    H5::FileAccPropList faplFile;
    faplFile.setLibverBounds(H5F_LIBVER_LATEST, H5F_LIBVER_LATEST);
    faplFile.setCore(sizeof(double)*length, false);

    H5::H5File file;
    file = H5::H5File("test-image.hdf5", H5F_ACC_TRUNC, H5::FileCreatPropList::DEFAULT);

    {
        std::string group_name = "test_group";
        size_t group_size_hint = 10*(group_name.size()+2);

        auto group = file.createGroup("test", group_size_hint);

        auto    dataspace = H5::DataSpace(1, (hsize_t*)&length);
        H5::IntType datatype(H5::PredType::NATIVE_DOUBLE);
        datatype.setOrder(H5T_ORDER_LE);

        auto dataspceChName=H5::DataSpace(H5S_SCALAR);

        for (int i =0; i <ch_count; ++i)
        {
            std::string chName="test_ch";

            auto dataset = group.createDataSet("test_channel"+ std::to_string(i), datatype, dataspace);
            dataset.write(v.data(), H5::PredType::NATIVE_DOUBLE);

            H5::StrType datatypeChName(H5::PredType::C_S1, chName.length()+1);
            datatypeChName.setSize(chName.length()+1);

            auto attribute = dataset.createAttribute("name", datatypeChName, dataspceChName);
            attribute.write(datatypeChName, chName.c_str());

            dataset.close();
        }
        dataspace.close();
        group.close();
    }

    // /* flush and get buffer */
    // file.flush(H5F_scope_t::H5F_SCOPE_GLOBAL);
    // auto requiredSize =H5Fget_file_image(file.getId(), NULL, 0);
    // auto buff = sg::make_unique_c_buffer<std::byte>(requiredSize);

    // /* write file */
    // {
    //     if (H5Fget_file_image(file.getId(), buff.get(), buff.size()) <0)
    //         throw std::runtime_error("error saving file");
    //     file.close();

    //     std::ofstream of("image.hdf5");
    //     of.write((char*)buff.get(), buff.size());
    // }

    /* write double-compressed */
    // {
    //     auto comp = sg::compression::zstd::compress(buff.get(), buff.size(), 6, 1);

    //     std::ofstream of("image.hdf5.zstd");
    //     of.write((char*)comp.get(), comp.size());
    // }

    H5Pclose(faplDataset);

    // std::cout << "raw size shoud be: " << std::to_string(length * ch_count * sizeof(double) / 1E6) << " MB" <<std::endl;
    // std::cout << "HDF5 size was: " << std::to_string(requiredSize/ 1E6) << " MB" <<std::endl;

    return 0;
}
