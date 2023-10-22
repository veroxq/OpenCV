#ifndef HUMANFACEDATABASE_H
#define HUMANFACEDATABASE_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class HumanFaceDataBase
{
public:
    HumanFaceDataBase();

    struct UserInfo{
        std::string name;
        std::string id;
        int age;
    };

    bool addUser(const UserInfo);
    
private:
    vector<FaceInfo> faces;
};

#endif // HUMANFACEDATABASE_H
