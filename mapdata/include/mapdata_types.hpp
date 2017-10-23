#ifndef MAPDATA_TYPES_HPP_
#define MAPDATA_TYPES_HPP_

#include <functional>

namespace vio {

template <typename T>
T CreateNewId() {
  return T();
}

// Note: Copy constructor will have the same id.
class UniqueId {
 public:
  // TODO: Maybe a random number?
  UniqueId() : id_(-1) {}

  int id() const { return id_; }

 protected:
  int id_;
};

// TODO: Learn how to not duplicate the code.
// Note: Copy constructor will have the same id.
class KeyframeId : public UniqueId {
 public:
  KeyframeId() { id_ = ++unique_id_; }

 private:
  static int unique_id_;
};

bool operator==(const KeyframeId &id0, const KeyframeId &id1) {
  return id0.id() == id1.id();
}

class LandmarkId : public UniqueId {
 public:
  LandmarkId() { id_ = ++unique_id_; }

 private:
  static int unique_id_;
};

bool operator==(const LandmarkId &id0, const LandmarkId &id1) {
  return id0.id() == id1.id();
}
typedef int FeatureId;

// Position of the feature in image.
struct FeatureMeasurement {
  float x, y;
};

struct Feature {
  FeatureMeasurement measurement;
  // TODO: Change to Eigen.
  // cv::Mat descriptor;
};

}  // vio

// TODO: Is there better way?
namespace std {
// Make hash for Id.
template <>
struct hash<vio::UniqueId> {
  std::size_t operator()(const vio::UniqueId &id) const {
    return std::hash<int>()(id.id());
  }
};

template <>
struct hash<vio::KeyframeId> {
  std::size_t operator()(const vio::KeyframeId &id) const {
    return std::hash<int>()(id.id());
  }
};

template <>
struct hash<vio::LandmarkId> {
  std::size_t operator()(const vio::LandmarkId &id) const {
    return std::hash<int>()(id.id());
  }
};

}  // std

#endif