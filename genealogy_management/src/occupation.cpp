#include <string>
#define oPointer Occupation*
using namespace std;
class Occupation {
   public:
    string getOccupationName() { return this->occupationName; }
    void setOccupationName(string occupationName) {
        this->occupationName = occupationName;
    }
    int getID() { return this->id; }
    void setID(int id) { this->id = id; }

   private:
    string occupationName;
    int id;
};