#include "StudentRecord.h"


StudentRecord::StudentRecord(){}


std::string StudentRecord::firstname() const { return firstname_; }
std::string StudentRecord::lastname() const { return lastname_; }
double StudentRecord::score() const { return score_; }


bool StudentRecord::operator>( StudentRecord const & right ) const {
  return this->score() > right.score();
};

bool StudentRecord::operator>=( StudentRecord const & right ) const {
  return this->score() >= right.score();
};

bool StudentRecord::operator<( StudentRecord const & right ) const {
  return this->score() < right.score();
};

bool StudentRecord::operator<=( StudentRecord const & right ) const {
  return this->score() <= right.score();
};

void StudentRecord::compute_score(void) {

  
  score_ = 0.0;
  for ( unsigned int i = 0; i < scores_.size(); ++i ) {
    double score = scores_[i];
    double weight = weights_[i];
    score_ += score * weight;
  }
  
}



std::ostream & operator<<( std::ostream & out, StudentRecord const &right ){ right.print(out); return out; }
std::istream & operator>>( std::istream & in, StudentRecord  &right ){ right.input(in); return in; }





void StudentRecordPhysics::print( std::ostream & out ) const  {
  out << lastname_ << "," << firstname_ << ", Scores : " << scores_[0] << "," << scores_[1] << ", Total :" << score();
}

bool StudentRecordPhysics::input( std::istream & in )  {
  // First add name (last,first)
  std::string line;
  std::getline( in, line, ',');
  lastname_ = line;
  std::getline( in, line, ',');
  firstname_ = line;
  // Now get each score. Physics has two, with weights 0.8 and 0.2
  std::getline( in, line, ',' );
  scores_.push_back( std::atof( line.c_str() ) );
  weights_.push_back( 0.8 );
  std::getline( in, line );
  scores_.push_back( std::atof( line.c_str() ) );
  weights_.push_back( 0.2 );
  if ( line == "") 
    return false;
  else {      
    compute_score();
    return true;
  }
}



void StudentRecordLiterature::print( std::ostream & out ) const  {
  out << lastname_ << "," << firstname_ << ", Scores : " << scores_[0] << "," << scores_[1] << "," << scores_[2] << ", Total:" << score();
}

bool StudentRecordLiterature::input( std::istream & in )  {
  // First add name (last,first)
  std::string line;
  std::getline( in, line, ',');
  lastname_ = line;
  std::getline( in, line, ',');
  firstname_ = line;
  // Now get each score. Literature has three, with weights 0.4, 0.4, 0.2
  std::getline( in, line, ',' );
  scores_.push_back( std::atof( line.c_str() ) );
  weights_.push_back( 0.4 );
  std::getline( in, line, ',' );
  scores_.push_back( std::atof( line.c_str() ) );
  weights_.push_back( 0.4 );
  std::getline( in, line );
  scores_.push_back( std::atof( line.c_str() ) );
  weights_.push_back( 0.2 );
  if ( line == "") 
    return false;
  else {
    compute_score();
    return true;
  }
}


void StudentRecordHistory::print( std::ostream & out ) const  {
  out << lastname_ << "," << firstname_ << ", Scores : " << scores_[0] << "," << scores_[1] << ", Total:" << score();
}

bool StudentRecordHistory::input( std::istream & in )  {
  // First add name (last,first)
  std::string line;
  std::getline( in, line, ',');
  lastname_ = line;
  std::getline( in, line, ',');
  firstname_ = line;
  // Now get each score. History has two. The highest score is weighted 0.6, the lower is 0.4
  std::getline( in, line, ',' );
  double score1 = std::atof( line.c_str() );
  std::getline( in, line );
  double score2 = std::atof( line.c_str() );    
  if ( score1 > score2 ) {
    scores_.push_back( score1 ); weights_.push_back( 0.6 );
    scores_.push_back( score2 ); weights_.push_back( 0.4 );
  } else {
    scores_.push_back( score2 ); weights_.push_back( 0.6 );
    scores_.push_back( score1 ); weights_.push_back( 0.4 );
  }
  if ( line == "") 
    return false;
  else {
    compute_score();
    return true;
  }
}

