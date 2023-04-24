import numpy as np

class StudentRecord :
    def __init__(self, line ) :
        self.firstname_ = ''
        self.lastname_ = ''
        self.score_ = None
        self.scores_ = None
        self.inputline(line)        
        
    def __str__(self):
        return self.lastname_ + ', ' + self.firstname_ + ', Scores : ' + ' '.join([str(x) for x in self.scores_]) + ', Total :' + str(self.score_)

    def firstname(self):
        return self.firstname_

    def lastname(self):
        return self.lastname_

    def score(self):
        return self.score_

    def inputline(self,data):        
        self.lastname_ = data[0]
        self.firstname_ = data[1]
        self.scores_ = np.array([ float(x) for x in data[2:] ])

    def calcscore(self):
        self.score_ = np.dot( self.scores_, self.weights_ )

class StudentRecordPhysics(StudentRecord):
    def __init__(self, line):
        StudentRecord.__init__(self, line)
        self.weights_ = np.array([ 0.8, 0.2])
        self.calcscore()

class StudentRecordLiterature(StudentRecord):
    def __init__(self, line):
        StudentRecord.__init__(self, line)
        self.weights_ = np.array([ 0.4, 0.4, 0.2])
        self.calcscore()

class StudentRecordHistory(StudentRecord):
    def __init__(self, line):
        StudentRecord.__init__(self, line)
        self.weights_ = np.array([ 0.4, 0.6 ])
        self.scores_ = sorted(self.scores_)
        self.calcscore()

