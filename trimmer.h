#ifndef _TRIM_
#define _TRIM_

#include<iostream>
#include<fstream>
#include<string>
#include "AudioFile.h"
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include<tuple>


/**
The function txt_to_songs() will extract the tracks listed on a txt file.
@param the name of the txt file
@return a vector with track names in it.


*/

std::vector<std::string> txt_to_songs(const std::string& file_name){
  std::string line;
  std::fstream fs;
  std::vector<std::string> tracks{};
  fs.open(file_name);
  if(fs.is_open()){
    while( getline(fs,line) ){
      std::cout<<line<<'\n';
      std::string track {};
      // have to locate the colon and parse
      // have to count the number of colons in a line and perform the appropriate action
      size_t colon_count = std::count_if(line.begin(),line.end(),[](const char& n){return n == ':';});
      if(colon_count == 1){
        auto colon_index = line.find(':');
        track = line.substr(colon_index+4);
        tracks.push_back(track);
      }
      else if(colon_count == 2){
        auto colon_index = line.find(':');
        line.erase(colon_index,1);
        auto second_colon_index = line.find(':');
        track = line.substr(second_colon_index+4);
        tracks.push_back(track);
      }
    }

    fs.close();
  }
  else {std::cout<<"File could not be opened.";}
  // i/o operations here
  return tracks;

}



/**
The function txt_to_everything will get the timestamps from a text file and convert them all to seconds.
It will also use the timestamps to get starting_points.
It will also extract the song names. Timestamps, starting_points, and Track names will be stored in a vector of std::tuples.
@param the name of the txt file (please include the extension)
@param the name of the song (please include the extension), but only WAV files work.
@return a vector a std::pairs containing Timestamps and starting_points.
*/
std::vector<std::tuple<int,std::string,int>> txt_to_everything(const std::string& file_name, AudioFile<double> song_to_sample, bool sample_load){


  double lengthInSeconds = song_to_sample.getLengthInSeconds(); // the last second of the song has to be known

  if(sample_load == 1){


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
    starting_points.push_back(static_cast<int>(lengthInSeconds));
    for(size_t index = 0; index < starting_points.size()-1; ++index){
      length_of_playback.push_back(starting_points[index+1]-starting_points[index]);
    }
    // putting the three vectors into one vector
  //   length_of_playback ;
  //   starting_points ;
  //   tracks ;
    for(size_t index = 0;index < length_of_playback.size();++index){
      std::tuple<int,std::string,int> ldt = {length_of_playback[index], tracks[index], starting_points[index]};
      packed_vector.push_back(ldt);
    }


    return packed_vector;
  }
  else{
    std::cout<<"File did not load."<<'\n';
    std::vector<std::tuple<int,std::string,int>> dummy_vec{};
    return dummy_vec;
  }
}


/**
The function txt_to_time() will get the timestamps of a text file and convert them all to seconds.
@param the name of the text file. Remember to include the extension.
@return a vector of timestamps converted to seconds.

*/

std::vector<int> txt_to_time(const std::string& file_name){

  std::string line;
  std::fstream fs;
  std::vector<int> starting_points{};
  fs.open(file_name);
  if(fs.is_open()){
    while( getline(fs,line) ){
      std::cout<<line<<'\n';
      int where_to_start {};
      // have to count the number of colons in a line and perform the appropriate action
      size_t colon_count = std::count_if(line.begin(),line.end(),[](const char& n){return n == ':';});
      // have to locate the colon and parse
      if(colon_count == 1){
        auto colon_index = line.find(':');
        where_to_start = std::stoi(line.substr(0,colon_index))*60 + std::stoi(line.substr(colon_index+1,2));
        starting_points.push_back(where_to_start);
      }
      else if(colon_count == 2){
        auto colon_index = line.find(':');
        where_to_start = std::stoi(line.substr(0,colon_index))*3600 + std::stoi(line.substr(colon_index+1,2))*60;
        line.erase(colon_index,1);
        auto second_colon_index = line.find(':');
        where_to_start += std::stoi(line.substr(second_colon_index+1,2));
        starting_points.push_back(where_to_start);
      }
      else{
        std::cout<<"File too long, keep the audio less than a day long..."<<'\n';
        fs.close();
      }

    }

    fs.close();
  }
  else {std::cout<<"File could not be opened.";}
  // i/o operations here
  return starting_points;
}

/**
The function txt_to_duration will extract data from a text file. It takes timestamps
and recursively returns the differences in seconds between consecutive timestamps.
@param the name of the txt file (please include the extension)
@param the name of the song (please include the extension), but only WAV files work.
@return a vector of durations in seconds for each song.

*/



std::vector<int> txt_to_duration(const std::string& file_name, const std::string& song_name){

  AudioFile<double> song_to_sample; //creating an audiofile object
  song_to_sample.load(song_name); // loading the wav file
  double lengthInSeconds = song_to_sample.getLengthInSeconds(); // the last second of the song has to be known


  std::vector<int> starting_points = txt_to_time(file_name); // call txt_to_time to read the file and provide starting_points
  starting_points.push_back(static_cast<int>(lengthInSeconds));
  std::vector<int> length_of_playback {};
  for (size_t index = 0; index < starting_points.size()-1; ++index){

    length_of_playback.push_back(starting_points[index+1]-starting_points[index]);
  }

  return length_of_playback;
}

/**
The function trim_audio() will partition a song for a certain amount of seconds and bounce back the name of the partition
@param std::string song_name, the source wav file that will get partitioned
@param int seconds, the number of resongs to 'record' the partition
@param int starting_timestamp, the starting point to 'record' in the source file. Must be in seconds.
@param std::string track_name, the name you want for the partition. It will come out a wav file.


*/



void trim_audio(int seconds, int starting_timestamp, const std::string& track_name, AudioFile<double> song_to_sample, bool sample_load){
// AudioFile gets put to use, but is a paramater now.


  if(sample_load == 1){


    // getting some stats about the wav file, wav is uncompressed audio
    song_to_sample.printSummary();
    // hoping to record audio up to a certain point and explore, achieved 11/4/23
    int channel = 0;
    int numSamples = song_to_sample.getNumSamplesPerChannel();
    float sampleRate = 44100.f; //sample rate default, dvd quality audio
    float frequency = 440.f;
    double length_in_seconds = song_to_sample.getLengthInSeconds();
    int numChannels = song_to_sample.getNumChannels();
    int numSamplesPerChannel = song_to_sample.getNumSamplesPerChannel() * ((seconds)/length_in_seconds); //magic numbers for one minute of the song played back

    int start = song_to_sample.getNumSamplesPerChannel() * ((starting_timestamp)/length_in_seconds);
    AudioFile<double>::AudioBuffer buffer;

    // Set number of samples per channel
    buffer.resize (2); // stereo audio
    buffer[0].resize (numSamplesPerChannel); // two channels to fill each has size of 'track' in terms of samples
    buffer[1].resize (numSamplesPerChannel); // resize the buffer to the where_to_start you want to record

    for (int i =0; i < numSamplesPerChannel; i++){ // where_to_start of recording is variable numSamplesPerChannel

      for (int channel = 0; channel < numChannels; channel++){
        song_to_sample.samples[channel][i] = song_to_sample.samples[channel][i+start]; //shifting the start of the playback with the start variable
      }


    }

    for (int i = 0; i < numSamplesPerChannel; i++){
     float sample = song_to_sample.samples[channel][i+start];

     for (int channel = 0; channel < numChannels; channel++){ // 'bouncing' the audio back to a hearable frequency
       buffer[channel][i] = sample;
     }
    }


    // put into the AudioFile object
    //song_to_sample.setAudioBuffer (buffer);

    //Resize the audio buffer
    // Set both the number of channels and number of samples per channel
    song_to_sample.setAudioBufferSize (numChannels, numSamplesPerChannel);
    // Set the number of samples per channel
    song_to_sample.setNumSamplesPerChannel (numSamplesPerChannel);
    // Set the number of channels
    song_to_sample.setNumChannels (numChannels);
    //Set bit depth and sample rate
    song_to_sample.setBitDepth (16);
    song_to_sample.setSampleRate (44100); //halves the length of the audio and highers pitch

    //Save the audio file to disk
    song_to_sample.save (track_name + ".wav",AudioFileFormat::Wave);

  }
  else{std::cout<<"File did not load."<<'\n';}

}

/**
The driver_function performs the actions of trimming and writing songs using previously made functions.
Songs you do not want trimmed will not be written if named 'delete' in the txt file.
Creates AudioFile object and loads song once. Will tell users of possible errors.
returns nothing but calls functions that return desired wav files.

*/



void driver_function(const std::string& file_name, const std::string& song_name){

    // want to load the song only once for efficiency...
  AudioFile<double> song_we_sample;
  bool sample_loaded = song_we_sample.load(song_name);

  // create that vector that stores all the data needed extracted from the text file.
  // function now needs Audiofile object and bool for loaded file == 1 to work.
  std::vector<std::tuple<int,std::string,int>> ldt_vector = txt_to_everything(file_name,song_we_sample, sample_loaded);

  size_t delete_counter = 0;
  try{
    for(size_t index = 0; index < ldt_vector.size();++index){
      if(std::get<1>(ldt_vector[index]) != "delete"){ //second element of tuple in whatever element of ldt_vector is a std::string
        // the order is mixed up now when accessing the tuple, but the same as trim_audio(song,where_to_start,starting_point,name_of_track)
        trim_audio(std::get<0>(ldt_vector[index]), std::get<2>(ldt_vector[index]), std::get<1>(ldt_vector[index]), song_we_sample, sample_loaded);
      }
    else{++delete_counter;}
    }

  }
  catch(const std::length_error&){std::cout<<"One or more timestamps might be in the wrong order, check if in chronological order please. You'll get the tracks up to where the mix up happened. Check also if song title contain any times ex. 3:00AM"<<'\n';}

  std::cout<<"Number of tracks created: "<<ldt_vector.size() - delete_counter<<'\n';

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
