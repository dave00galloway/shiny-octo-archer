#include "gmock/gmock.h"

using namespace ::testing;

class DifficultCollaborator {
public:
   virtual bool calculate(int* result) 
   {
      throw 1;
   }
};

class Target {
public:
   int execute(DifficultCollaborator* calculator) {
      int i;
      if (!calculator->calculate(&i))
         return 0;
      return i;
   }
};

class DifficultCollaboratorMock: public DifficultCollaborator {
public:
   MOCK_METHOD1(calculate, bool(int*));
};

TEST(ATarget, ReturnsAnAmountWhenCalculatePasses) {
   DifficultCollaboratorMock difficult;
   Target calc;
   EXPECT_CALL(difficult, calculate(_))
      .WillOnce // the mock object will perfrom the following actions once
	  (DoAll // yes, all of these!
	   ( // when the calculate method of the mock is called
         SetArgPointee<0>(3), // the first argument willbe set to 3 by the mock system
         Return(true))); // and will return true

   auto result = calc.execute(&difficult);

   ASSERT_THAT(result, Eq(3)); // what we are actually testing, the Target object (not the mock difficultCollablorsator!) returns the value 3 
}
