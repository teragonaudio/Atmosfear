/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_97598758_INCLUDED
#define BINARYDATA_H_97598758_INCLUDED

namespace BinaryData
{
    extern const char*   keywords_txt;
    const int            keywords_txtSize = 594;

    extern const char*   LICENSE;
    const int            LICENSESize = 1053;

    extern const char*   README_markdown;
    const int            README_markdownSize = 123;

    extern const char*   CMakeLists_txt;
    const int            CMakeLists_txtSize = 2032;

    extern const char*   LICENSE_md;
    const int            LICENSE_mdSize = 1458;

    extern const char*   README_md;
    const int            README_mdSize = 4015;

    extern const char*   mkbuild_sh;
    const int            mkbuild_shSize = 1921;

    extern const char*   README_txt;
    const int            README_txtSize = 3767;

    extern const char*   LICENSE_txt;
    const int            LICENSE_txtSize = 1296;

    extern const char*   README_md2;
    const int            README_md2Size = 11869;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 10;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
