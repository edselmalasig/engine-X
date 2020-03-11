#include <stdio.h>
#include <string.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::string pathstr;
std::vector<unsigned int> indices;
std::vector<unsigned int> vt_indices;
std::vector<unsigned int> vn_indices;

int main()
{
     std::ifstream objFile;
     std::string objLine;
     std::vector<std::string> lineinfile;
     pathstr = "models/explodedcube.obj";

     //objFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
     try{
          objFile.open(pathstr);
          std::stringstream objStream;

          while (std::getline(objFile, objLine)){
               if(objLine.at(0) == 'f' || objLine.at(0) == 'F'){
                    lineinfile.push_back(objLine);
               }
          }
          objFile.close();

     }catch(std::ifstream::failure e){
          std::cout << "ERROR : OBJ FILE : FILE_NOT_SUCCESFULLY_READ." << std::endl;
     }

     int tmp;
     for(std::vector<std::string>::iterator it = lineinfile.begin(); it != lineinfile.end(); it++)
     {
          //std::cout << *it << std::endl;
          int spacepos=0, bspos=0, bspcount=0;
          for(unsigned int i=0; i < it->length(); i++)
          {
               if(it->at(i)=='/')
                    bspcount++;
          }
          std::cout << *it << std::endl;
          std::string str;
          if(bspcount == 6){
               spacepos = it->find(" ");
               bspos = it->find("/");
               str = it->substr(spacepos, bspos-1);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find(" ", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vn_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find(" ", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vn_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               str = it->substr(spacepos+1, it->length());
               vn_indices.push_back(stoull(str));
          }
          if(bspcount == 8){
               spacepos = it->find(" ");
               bspos = it->find("/");
               str = it->substr(spacepos, bspos-1);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find(" ", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vn_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find(" ", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vn_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find(" ", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vn_indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               indices.push_back(stoull(str));

               spacepos = bspos;
               bspos = it->find("/", bspos+1);
               str = it->substr(spacepos+1, bspos - 1 - spacepos);
               vt_indices.push_back(stoull(str));

               spacepos = bspos;
               str = it->substr(spacepos+1, it->length());
               vn_indices.push_back(stoull(str));
          }


          if(bspcount > 8 || bspcount < 6){
               std::cout << "ERROR : BAD MODEL FILE : Wrong indices count." << std::endl;
          }
     }
     for(unsigned int i = 0; i < indices.size(); i++)
     {
          std::cout << indices.at(i) << "/" << vt_indices.at(i) << "/" << vn_indices.at(i)
          //<< " " << indices.at(i) << "/" << vt_indices.at(i) << "/" << vn_indices.at(i)
          //<< " " << indices.at(i) << "/" << vt_indices.at(i) << "/" << vn_indices.at(i)
          << std::endl;
     }

}
