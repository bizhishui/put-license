// --------------------------------------------------- //
//                     put-license                     //
//         Copyright (c) 2014 Mikhail Artemyev         //
//     See LICENSE.txt file for license information    //
// --------------------------------------------------- //

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;



int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cout << "\nUsage:\n./put_license <path/to/dir> <license_template.txt>\n";
    std::cout << "<path/to/dir> - path to top-level directory containing .hpp, .cpp files and/or subdirectories (search goes recursively)\n";
    std::cout << "<license_template.txt> - a file containing a license info which will be put in each file\n\n";
    std::cout << "Example:\n" << argv[0] << " ../test ../test/license_header.txt\n\n";
    return 1;
  }

  // top-level directory from which we start looking for .hpp and .cpp files
  std::string top_dir = std::string(argv[1]);
  // a name of a file containig license info
  std::string license_file = std::string(argv[2]);

  // check that the top-level dir and license file exist
  if (!fs::exists(top_dir))
    throw std::runtime_error("Top-level directory '" + top_dir + "' doesn't exist");
  else // if it exists, check that it's directory
    if (!fs::is_directory(top_dir))
      throw std::runtime_error("Given top-level directory '" + top_dir + "' is not really a directory");
  if (!fs::exists(license_file))
    throw std::runtime_error("File with license info '" + license_file + "' doesn't exist");


  // read the license information from the corresponding given file
  std::string license_info;
  std::ifstream in(license_file.c_str());
  if (!in)
    throw std::runtime_error("File '" + license_file + "' can't be opened for reading");
  in.seekg(0, std::ios::end);
  license_info.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&license_info[0], license_info.size());
  in.close();


  // a map between a file extension and a key word that means the beginning of the
  // useful part of the file. the license information will be put to only those files
  // that have an extension from this map
  std::map<std::string, std::string> ext_map;
  ext_map[".hpp"] = "#ifndef"; // a key word from which the file with .hpp extension begins 
  ext_map[".cpp"] = "#include"; // a key word from which the file with .cpp extension begins 


  // go to each file recursively starting from top-level directory
  fs::recursive_directory_iterator dir(top_dir), end;
  while (dir != end)
  {
    // a full canonical name of the current file
    const std::string filename = fs::canonical(dir->path()).string();
    // get a file extension
    std::string file_extension = fs::extension(filename);
    // if the extenstion belongs to the map, we put the license info into it.
    // the license info is put at the beginning of the file.
    // the beginning of the file is defined by a key word described in the map
    // NOTE!
    // if there is something before first key word in a file, it will be lost!

    std::map<std::string, std::string>::const_iterator iter = ext_map.find(file_extension);

    if (iter != ext_map.end()) // if the extension is from the list, we put the license into the file
    {
      // read the file
      std::string file_content;
      std::ifstream in(filename.c_str());
      if (!in)
        throw std::runtime_error("File '" + filename + "' can't be opened for reading");
      in.seekg(0, std::ios::end);
      file_content.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&file_content[0], file_content.size());
      in.close();

      // change a part of the content in the beginning of the file
      size_t pos = file_content.find(iter->second);
      if (pos == file_content.npos)
        throw std::runtime_error("Necessary substring '" + iter->second + "' not found");

      // make a new file with the same name
      std::ofstream out(filename.c_str());
      if (!out)
        throw std::runtime_error("File '" + filename + "' can't be opened for writing");
      // write a license information
      out << license_info;
      // write all file's content
      out << file_content.substr(pos);
      out.close();
    }

    ++dir;

  } // pass through all files recursively

  return 0;
}

