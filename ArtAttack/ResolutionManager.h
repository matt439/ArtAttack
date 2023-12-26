#ifndef RESOLUTIONMANAGER_H
#define RESOLUTIONMANAGER_H

#include <string>
//#include "SimpleMath.h"
#include "MattMath.h"
#include "screen_resolution.h"



class ResolutionManager
{
private:
    screen_resolution _resolution = screen_resolution::S_1280_720;

    MattMath::Vector2I convert_resolution_to_ivec(
        screen_resolution resolution) const;
    MattMath::Vector2F convert_resolution_to_vec(
        screen_resolution resolution) const;
    screen_resolution convert_string_to_resolution(
        const std::string& string) const;
    screen_resolution convert_vec_to_resolution(
        const MattMath::Vector2F& vec) const;
    screen_resolution convert_ivec_to_resolution(
        const MattMath::Vector2I& vec) const;

public:
    ResolutionManager() {}
    MattMath::Vector2I get_resolution_ivec() const;
    MattMath::Vector2F get_resolution_vec() const;
    std::string get_resolution_string() const;
    screen_resolution get_resolution() const { return this->_resolution; }
    void set_resolution(screen_resolution resolution);
    void set_resolution(const std::string& resolution);
    void set_resolution(const MattMath::Vector2F& resolution);
    void set_resolution(const MattMath::Vector2I& resolution);
    std::string convert_resolution_to_string(
        screen_resolution resolution) const;


};
#endif // !RESOLUTION_H
