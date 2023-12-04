#include<iostream>
#include<fstream>
#include<string>
#include "AudioFile.h"
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include<tuple>
#include "trimmer.h"


int main () {

  //
  const std::string name_of_song {"El y Yo Franco Escamilla.wav"}; // please include extension and make sure its a WAV file.

  const std::string name_of_txt_file {"doomer.txt"}; // include the extension

  driver_function(name_of_txt_file, name_of_song);


////// T H E  G R A V E Y A R D ///////////
/*      else if(std::get<1>(ldt_vector[index]) == "merge"){
        size_t front_index = index;
        while(std::get<1>(ldt_vector[index - 1]) == "delete"){
            index -= 1;
        }
        trim_audio(std::get<2>(ldt_vector[front_index]) - std::get<2>(ldt_vector[index]), std::get<2>(ldt_vector[index]), std::get<1>(ldt_vector[index]), song_we_sample, sample_loaded);
      }
*/
  //   for(size_t index = 0; index < partitions.size();++index){
//     if(partitions[index] != "delete"){
//       trim_audio(name_of_song, length_of_parts[index], times[index], partitions[index]);
//     }
//     else{}
//   }
  //   std::vector<int> times = txt_to_time(name_of_txt_file); // three vectors created, txt file read three times ... need to fix
//   std::vector<std::string> partitions = txt_to_songs(name_of_txt_file);
//   std::vector<int> length_of_parts = txt_to_duration(name_of_txt_file,name_of_song);
  // this loop will check for any songs named delete and remove them from the vectors, also removing other stats of the songs.
  // if removing changes the size of the vector put a counter for how many deletes and shift the index
  // according to the counter
//   size_t delete_counter = 0;
//   for(size_t index = 0;index < partitions.size();++index){
//     if(partitions[index - delete_counter] == "delete"){
//       partitions.erase(partitions.begin() + (index - delete_counter)); //iterator math, erasing each element from the vectors
//       times.erase(times.begin() + (index - delete_counter));           // at the index where 'delete' was found
//       length_of_parts.erase(length_of_parts.begin() + (index - delete_counter));
//       delete_counter+=1;
//     }
//     // when delete is not found, go ahead of write the track
//   else{trim_audio(name_of_song, length_of_parts[index - delete_counter], times[index - delete_counter], partitions[index - delete_counter]);}
//   } YOU OVERTHINK SOMETIMES
//   std::vector<int> times = txt_to_time("Colour My World timestamps.txt");
//   std::vector<std::string> partitions = txt_to_songs("Colour My World timestamps.txt");
//   std::vector<int> length_of_parts = txt_to_duration("Colour My World timestamps.txt","Colour My World");
//   trim_audio("Colour My World",60,0,"piano solo");
//   trim_audio("Colour My World", 60, 60, "vocal solo"); //so far you can tell it how much to record but must start from beginning.
//   trim_audio("Colour My World",60,120,"flute solo");
//need to make new starting point
  return 0;
}

// CopyRight statement for using AudioFile
/*Copyright (c) 2017 Adam Stark

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
