#include "CameraStreamer.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <sstream>


int main(int argc, char**argv)
{
    int index_drop=25;
    vector<int> cap_drop_vec;
    vector<int> cap_count_vec;
    if(argc>=2)
    {
      stringstream ss;
      ss<<argv[1];
      cout<<"ss:"<<ss.str()<<endl;
      ss>>index_drop;
      //index_drop=argv[1];
    }
                printf("%s\n", "begin");
    //IP camera URLs
    // vector<string> capture_source = {
    //     "rtsp://192.168.2.100/profile2/media.smp",
    //     "rtsp://192.168.0.100/profile2/media.smp"
    // };
    // vector<string> capture_source = {
    //     "/storage2/public/Surveilliance/zhongshan_dface/Network Video Recorder_192.168.0.244_1_20170531074045_20170531081605_1496204460609.mp4",
    //     "/storage2/public/Surveilliance/zhongshan_dface/Network Video Recorder_192.168.0.244_1_20170531123508_20170531131022_1496281166984.mp4"
    // };
 
        // "/storage2/public/Surveilliance/zhongshan_dface/20170601/Network Video Recorder_27.42.165.79_2_20170601170836_20170601174352_1496415598396.mp4",
        // "/storage2/public/Surveilliance/zhongshan_dface/20170601/Network Video Recorder_27.42.165.79_2_20170601174352_20170601181908_1496425474706.mp4"
   
        //"/storage2/liushuai/work_code/camera/build/1.mp4",
    vector<string> capture_source = {
        "/storage2/liushuai/work_code/camera/build/DJI_0008.MOV"
    };
string output_dir="/storage2/liushuai/work_code/camera/build/test/";
      cout<<"index_drop:"<<index_drop<<endl;
    cap_drop_vec.clear();
    cap_count_vec.clear();
    for (int i = 0; i < capture_source.size(); i++)
    {
      cap_drop_vec.push_back(index_drop);
      cap_count_vec.push_back(index_drop);
    }
    //USB Camera indices
    vector<int> capture_index = { 0, 1 };
 
    //Highgui window titles
    vector<string> label;
    for (int i = 0; i < capture_source.size(); i++)
    {
        string title = "CCTV " + to_string(i);
        label.push_back(title);
    }
 
    //Make an instance of CameraStreamer
                printf("%s\n", "1");
    CameraStreamer cam(capture_source);
  long long totalframes = cam.camera_capture[0]->get(CAP_PROP_FRAME_COUNT);
 
                printf("totalframes %lld\n", totalframes);
unsigned  int ii=0;
unsigned  int j=0;
unsigned  int k=0;
unsigned  int z=0;
    while (waitKey(20) != 27)
    {
        //Retrieve frames from each camera capture thread
        for (int i = 0; i < capture_source.size(); i++)
        {
            Mat frame;
            //Pop frame from queue and check if the frame is valid
                printf("%s\n", "try_pop");
            if (cam.frame_queue[i]->try_pop(frame))
            {
                totalframes--;
                if(totalframes<=0)
                {
                    cout<<"pic over"<<endl;
                    return 0;
                }
              if(cap_count_vec[i]%cap_drop_vec[i] !=0)
              {
                  cap_count_vec[i]=(cap_count_vec[i]+1)%cap_drop_vec[i];
                  continue;
              }
              int fps = cam.camera_capture[i]->get(CAP_PROP_FPS);
              cout<<i<<"vedio fps:"<<fps<<endl;
              cout<<i<<"vedio drop count:"<<cap_drop_vec[i]<<endl;
              cap_count_vec[i]=(cap_count_vec[i]+1)%cap_drop_vec[i];
                    //Show frame on Highgui window
                    //imshow(label[i], frame);
                //printf("%s\n", "pop");
                    //imwrite("/storage2/liushuai/work_code/camera/build/test.jpg",frame);
                    //return 0;
                ii++;
                if (4294967295 == ii)
                {
                    /* code */
                    ii=0;
                    j++;
                    if (4294967295 == j)
                    {
                        i=0;
                        k++;
                        if (4294967295 == k)
                        {
                            k=0;
                            z++;
                        }
                    }
                }
                string filename=to_string(z)+"_"+to_string(k)+"_"+to_string(j)+"_"+to_string(ii);
                string outname = output_dir +"/" + filename + ".jpg";
                imwrite(outname, frame);

            }
        }
    }
}