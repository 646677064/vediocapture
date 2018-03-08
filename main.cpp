#include "CameraStreamer.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <sstream>


int main(int argc, char**argv)
{
    int index_drop=58;
    int iey_max_frame=100;
    vector<int> cap_drop_vec;
    vector<int> cap_count_vec;
    vector<long long> cap_whole_frame;
    string filename="";
    string dirname="";
    if(argc>=5)
    {
      stringstream ss;
      ss<<argv[1];
      cout<<"ss:"<<ss.str()<<endl;
      ss>>index_drop;

      stringstream ss1;
      ss1<<argv[2];
      cout<<"argv 2:"<<ss1.str()<<endl;
      ss1>>iey_max_frame;


      stringstream ss2;
      ss2<<argv[3];
      cout<<"argv 3:"<<ss2.str()<<endl;
      ss2>>filename;
      //index_drop=argv[1];
      stringstream ss3;
      ss3<<argv[4];
      cout<<"argv 4:"<<ss3.str()<<endl;
      ss3>>dirname;
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
      string filepath="/storage2/liushuai/work_code/camera/build/";
      string str1 = filepath + filename;
    vector<string> capture_source = {
        str1
    };

    CameraStreamer cam(capture_source,index_drop,iey_max_frame);

string output_dir="/storage2/liushuai/work_code/camera/build/pic/test";
output_dir= output_dir+dirname;
output_dir= output_dir+"/";
      cout<<"output_dir:"<<output_dir<<endl;
      cout<<"index_drop:"<<index_drop<<endl;
    cap_drop_vec.clear();
    cap_count_vec.clear();
    cap_whole_frame.clear();
    for (int i = 0; i < capture_source.size(); i++)
    {
      cap_drop_vec.push_back(index_drop);
      cap_count_vec.push_back(index_drop);
     int totalframes = cam.camera_capture[i]->get(CAP_PROP_FRAME_COUNT);
      int fps = cam.camera_capture[i]->get(CAP_PROP_FPS);
      cap_whole_frame.push_back(totalframes/index_drop);
      printf("totalframes %lld fps %d \n", totalframes,fps);
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
            if (cam.frame_queue[i]->try_pop(frame))
            {
                printf("%s %lld \n", "try_pop",cap_whole_frame[i]);
                cap_whole_frame[i]--;
                if(cap_whole_frame[i]<=0)
                {
                    cout<<"pic over : "<<i<<endl;
                    return 0;
                }
              // if(cap_count_vec[i]%cap_drop_vec[i] !=0)
              // {
              //     cap_count_vec[i]=(cap_count_vec[i]+1)%cap_drop_vec[i];
              //     continue;
              // }
              // int fps = cam.camera_capture[i]->get(CAP_PROP_FPS);
              // cout<<i<<"vedio fps:"<<fps<<endl;
              // cout<<i<<"vedio drop count:"<<cap_drop_vec[i]<<endl;
              // cap_count_vec[i]=(cap_count_vec[i]+1)%cap_drop_vec[i];
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
      cout<<"main over:"<<endl;
}