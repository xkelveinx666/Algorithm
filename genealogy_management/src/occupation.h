#include <string>
#define oPointer Occupation*
using namespace std;
class Occupation {
   public:
    string getOccupationName() { return this->occupationName; }
    void setOccupationName(string occupationName) {
        this->occupationName = occupationName;
    }

   private:
    string occupationName;
};