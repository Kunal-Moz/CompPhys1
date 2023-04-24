#include "StudentRecord.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <numeric>
#include <memory>
#include <algorithm>


typedef std::shared_ptr<StudentRecord> StudentRecordPtr;
typedef std::vector<StudentRecordPtr> StudentRecordColl;

bool comparescore( StudentRecordPtr const & r1, StudentRecordPtr const & r2 ){
  return *r1 < *r2; 
}

int main(int argc, char * argv[]){




  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " filename.txt" << std::endl;
    return 0;
  }
  std::ifstream fin( argv[1] );


  StudentRecordColl records, physics, literature, history;
  bool valid = true;
  while( valid ) {
    std::string line;
    std::getline( fin, line, ',');
    if ( line == "" ) 
      break;

    if ( line == "Physics" ) {
      StudentRecordPtr irecord( new StudentRecordPhysics() );
      valid = irecord->input(fin);
      if ( valid ) {
	records.push_back( irecord );
	physics.push_back( irecord );
      }
      else
	break;
    } else if ( line == "Literature" ) {
      StudentRecordPtr irecord( new StudentRecordLiterature() );
      valid = irecord->input(fin);
      if ( valid ) {
	records.push_back( irecord );
	literature.push_back( irecord );
      }
      else
	break;
    } else if ( line == "History" ) {
      StudentRecordPtr irecord( new StudentRecordHistory() );
      valid = irecord->input(fin);
      if ( valid ) {
	records.push_back( irecord );
	history.push_back( irecord );
      }
      else
	break;
    } else {
      std::cout << "Invalid input, ignoring" << std::endl;
      continue;
    }

  }

  auto groups = { std::make_tuple("All", &records),
		  std::make_tuple("Physics", &physics),
		  std::make_tuple("History", &history),
		  std::make_tuple("Literature", &literature)};

  for ( auto group : groups ) {
    auto name = std::get<0>( group );
    auto & vals = std::get<1>( group );
    std::cout << "------------ " << name << " --------" << std::endl;
    std::sort( vals->begin(), vals->end(), comparescore );
    std::cout << "Values: " << std::endl;
    std::vector<double> scores;
    for ( auto member : *vals ) {
      std::cout << *member << std::endl;
      scores.push_back( member->score() );
    }    
    double average = std::accumulate( scores.begin(), scores.end(), 0.);
    if ( scores.size() > 0 )
      average /= scores.size();
    std::cout << "Average : " << average << std::endl;
    
  }

  
}
