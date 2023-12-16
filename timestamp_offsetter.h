#ifndef __OFFSET__
#define __OFFSET__

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

/*
The function timestamp_offsetter will change the timestamps of a txt file.
It will relabel the first timestamp as 00:00:00 and add to the timestamp according to durations.
Of the original txt file.
@param The original txt file
@return A txt file with the updated timestamps.

**/


std::vector<std::tuple<int,std::string,int>> txt_to_everything(const std::string& file_name){


  //double lengthInSeconds = song_to_sample.getLengthInSeconds(); // the last second of the song has to be known

  //if(sample_load == 1){


  //   std::vector<int> starting_points = txt_to_time(file_name); // call txt_to_time to read the file and provide starting_points

    std::vector<int> length_of_playback{};
    std::vector<int> starting_points{};
    std::vector<std::string> tracks{};


    std::string line;
    std::fstream fs;
    std::vector<std::tuple<int,std::string,int>> packed_vector {};
    fs.open(file_name);
    if(fs.is_open()){
      while( getline(fs,line) ){
        std::cout<<line<<'\n';
        // starting point and track section...
        int where_to_start {};
        std::string track {};
        // have to count the number of colons in a line and perform the appropriate action
        size_t colon_count = std::count_if(line.begin(),line.end(),[](const char& n){return n == ':';});
        // have to locate the colon and parse
        if(colon_count == 1){
          auto colon_index = line.find(':');
          try{
            where_to_start = std::stoi(line.substr(0,colon_index))*60 + std::stoi(line.substr(colon_index+1,2));
          }
          catch(const std::invalid_argument&){std::cout<<"Message to User: Timestamps come first in the text file, not track titles."<<'\n';}
          starting_points.push_back(where_to_start);
          track = line.substr(colon_index+4);
          tracks.push_back(track);
        }
        else if(colon_count == 2){
          auto colon_index = line.find(':');
          try{
            where_to_start = std::stoi(line.substr(0,colon_index))*3600 + std::stoi(line.substr(colon_index+1,2))*60;
          }
          catch(const std::invalid_argument&){std::cout<<"Message to User: Timestamps come first in the text file, not track titles."<<'\n';}
          line.erase(colon_index,1);
          auto second_colon_index = line.find(':');
          where_to_start += std::stoi(line.substr(second_colon_index+1,2));
          starting_points.push_back(where_to_start);
          track = line.substr(second_colon_index+4);
          tracks.push_back(track);

        }
        else{
          std::cout<<"File too long, keep the audio less than a day long...three colons found in one line."<<'\n';
          std::cout<<"If this isn't the case, please undo double spacing in the txt file and remove empty lines."<<'\n';
          std::cout<<"You get the first tracks until the first empty line."<<'\n';
          fs.close();
        }

      }

      fs.close();
    }
    else {std::cout<<"File could not be opened.";}
    // i/o operations here

    //starting_points section...
    //starting_points.push_back(static_cast<int>(lengthInSeconds));
    for(size_t index = 0; index < starting_points.size()-1; ++index){
      length_of_playback.push_back(starting_points[index+1]-starting_points[index]);
    }
    // putting the three vectors into one vector
    //   length_of_playback ;
    //   starting_points ;
    //   tracks ;
    for(size_t index = 0;index < starting_points.size();++index){
      std::tuple<int,std::string,int> ldt = {length_of_playback[index], tracks[index], starting_points[index]};
      packed_vector.push_back(ldt);
    }


    return packed_vector;
  /*}
  else{
    std::cout<<"File did not load."<<'\n';
    std::vector<std::tuple<int,std::string,int>> dummy_vec{};
    return dummy_vec;
  }*/
}

void driver_function(const std::string& file_name){

    // want to load the song only once for efficiency...
  //AudioFile<double> song_we_sample;
  //bool sample_loaded = song_we_sample.load(song_name);

  // create that vector that stores all the data needed extracted from the text file.
  // function now needs Audiofile object and bool for loaded file == 1 to work.
  std::vector<std::tuple<int,std::string,int>> ldt_vector = txt_to_everything(file_name);

  size_t delete_counter = 0;
  try{
    for(size_t index = 0; index < ldt_vector.size();++index){
      if(std::get<1>(ldt_vector[index]) != "delete"){ //second element of tuple in whatever element of ldt_vector is a std::string
        // the order is mixed up now when accessing the tuple, but the same as trim_audio(song,where_to_start,starting_point,name_of_track)
        std::cout<<std::get<0>(ldt_vector[index])<<' '<<std::get<2>(ldt_vector[index])<<' '<<std::get<1>(ldt_vector[index])<<'\n';
      }
    else{++delete_counter;}
    }

  }
  catch(const std::length_error&){std::cout<<"One or more timestamps might be in the wrong order, check if in chronological order please. You'll get the tracks up to where the mix up happened. Check also if song title contain any times ex. 3:00AM"<<'\n';}

  std::cout<<"Number of tracks created: "<<ldt_vector.size() - delete_counter<<'\n';

  std::ofstream new_file;
  new_file.open("translated " + file_name); //these for loops convert a given starting point (secs) to its timestamp (HH:MM:SS)
  std::string og_point{"00:00:00"};
  int time = 0;
  new_file << og_point + ' ' + std::get<1>(ldt_vector[0]) + '\n';
  for(size_t index = 1; index < ldt_vector.size(); ++index){
      time += std::get<0>(ldt_vector[index - 1]);
      int hours = time/3600; // remaining hours
      int minutes = (time - hours*3600)/60; // remaining minutes
      int seconds = time - hours*3600 - minutes*60; // remaining seconds
      if(minutes < 10 and seconds < 10){
        std::string hours_str = '0' + std::to_string(hours);
        std::string minutes_str = '0' + std::to_string(minutes);
        std::string seconds_str = '0' + std::to_string(seconds);
        new_file << hours_str + ':' + minutes_str + ':' + seconds_str + ' ' + std::get<1>(ldt_vector[index]) + '\n';
      }
      else if(minutes < 10 and seconds > 10){ //trimmer code needs '07' or '00' for example to work if in MM:SS format
        std::string hours_str = '0' + std::to_string(hours); //adding a 0 to string, hours should always be less than 10 in most cases.
        std::string minutes_str = '0' + std::to_string(minutes); // adding a 0 to string, when MM < 10.
        //std::string seconds_str = '0' + std::to_string(seconds);
        new_file << hours_str + ':' + minutes_str + ':' + std::to_string(seconds) + ' ' + std::get<1>(ldt_vector[index]) + '\n';
      }
      else if(minutes > 10 and seconds < 10){ //need to separate the cases, can't just write to file in one iteration.
        //std::string minutes_str = '0' + std::to_string(minutes);
        std::string hours_str = '0' + std::to_string(hours);
        std::string seconds_str = '0' + std::to_string(seconds);
        new_file << hours_str + ':' + std::to_string(minutes) + ':' + seconds_str + ' ' + std::get<1>(ldt_vector[index]) + '\n';
      }
      else{
        std::string hours_str = '0' + std::to_string(hours);
        new_file << hours_str + ':' + std::to_string(minutes) + ':' + std::to_string(seconds) + ' ' + std::get<1>(ldt_vector[index]) + '\n';
      }
  }
  new_file.close();
  std::cout<<"DONE. OWARI"<<'\n';
    // try-block in case the user mixes up the order of the timestamps
  // use this when the project is finished, too early to account for all errors.
//   try{
//     for(size_t index = 0; index < ldt_vector.size();++index){
//       if(std::get<1>(ldt_vector[index]) != "delete"){ //second element of tuple in whatever element of ldt_vector is a std::string
//     // the order is mixed up now when accessing the tuple, but the same as trim_audio(song,where_to_start,starting_point,name_of_track)
//         trim_audio(song_name, std::get<0>(ldt_vector[index]), std::get<2>(ldt_vector[index]), std::get<1>(ldt_vector[index]), song_to_sample, sample_load);
//       }
//       else{}
//     }
//   }
//   catch(const std::length_error&){std::cout<<"One or more timestamps might be in the wrong order, check if in chronological order please. You'll get the tracks up to where the mix up happened."<<'\n';}

}


#endif
