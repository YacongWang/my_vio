#include "feature_tracker.hpp"

#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

namespace vio {

class FeatureTrackerOCV : public FeatureTracker {
 public:
  enum DetectorType { UNKNOWN = 0, DETECTORONLY, DETECTORDESCRIPTOR };

  FeatureTrackerOCV(FeatureTrackerOptions options,
                    std::unique_ptr<FeatureMatcher> matcher);
  FeatureTrackerOCV() = delete;

  virtual bool TrackFirstFrame(ImageFrame &output_frame) override;
  virtual bool TrackFrame(const ImageFrame &prev_frame,
                          ImageFrame &output_frame,
                          std::vector<cv::DMatch> &matches) override;
  // Use match approach when lost tracking.
  virtual bool MatchFrame(const ImageFrame &prev_frame,
                          ImageFrame &output_frame,
                          std::vector<cv::DMatch> &matches) override;

 protected:
  void ComputeFeatures(ImageFrame &frame);

  DetectorType detector_type_;
  int max_feature_per_frame_;
  cv::Ptr<cv::Feature2D> detector_;
  cv::Ptr<cv::DescriptorExtractor> descriptor_;
};

}  // vio
