#include "CameraStreamer.hpp"
 
 const int default_interval_drop=12;

 const int default_keep_frame=50;

CameraStreamer::CameraStreamer(vector<string> stream_source)
{
	camera_source = stream_source;
	camera_count = camera_source.size();
	isUSBCamera = false;
 
	m_intervaldrop = default_interval_drop;
	m_keepframe = default_keep_frame;
	m_brun=false;
	startMultiCapture();
}
 
CameraStreamer::CameraStreamer(vector<int> capture_index)
{
	camera_index = capture_index;
	camera_count = capture_index.size();
	isUSBCamera = true;
	m_intervaldrop = default_interval_drop;
	m_keepframe = default_keep_frame;
 
	m_brun=false;
	startMultiCapture();
}
 
CameraStreamer::CameraStreamer(vector<string> stream_source,int intervaldrop,int imax_keep_frame)
{
	camera_source = stream_source;
	camera_count = camera_source.size();
	isUSBCamera = false;
	//m_intervaldrop=default_interval_drop;
	 m_intervaldrop = intervaldrop;
	//m_keepframe=default_keep_frame;
	 m_keepframe = imax_keep_frame;
	m_brun=false;
	startMultiCapture();
}

CameraStreamer::~CameraStreamer()
{
	cout<<" ~CameraStreamer over===1"<<endl;
	stopMultiCapture();
	cout<<" ~CameraStreamer over==="<<endl;
}
 
void CameraStreamer::captureFrame(int index)
{
// VideoCapture *capture = camera_capture[index];
// while (true)
// {
// Mat frame;
// //Grab frame from camera capture
// (*capture) >> frame;
// //Put frame to the queue
// frame_queue[index]->push(frame);
// //relase frame resource
// frame.release();
// }
	VideoCapture *capture = camera_capture[index];
	int intervaldrop = m_intervaldrop;
	int count_sum=0;
	cout<<m_keepframe<<" "<<intervaldrop<<endl;
	//bool bdo=false;
	while (true)
	{
		if (!m_brun)
		{
			return;//break;
			/* code */
		}
		//cout<<m_keepframe<<" test=========="<<intervaldrop<<" "<<frame_queue[index]->unsafe_size()<<endl;
          if (frame_queue[index]->unsafe_size()>=m_keepframe)//unsafe_size
          {
          	sleep(2);
          	continue;
          }
		Mat frame;
		//Grab frame from camera capture
		(*capture) >> frame;
        //Pop frame from queue and check if the frame is valid
		long long totalframes = capture->get(CAP_PROP_FRAME_COUNT);
    	long long frame_pos = capture->get(cv::CAP_PROP_POS_FRAMES);

		cout<<totalframes<<" test=========="<<frame_pos<<" "<<endl;
    	if (frame_pos >= totalframes)
    	{
				frame.release();
    		return;
    	}
          if(count_sum%intervaldrop !=0)
          {
              count_sum=(count_sum+1)%intervaldrop;
			//relase frame resource
				frame.release();
              continue;
          }
          else
          {
			//Put frame to the queue
			frame_queue[index]->push(frame);
          	count_sum=(count_sum+1)%intervaldrop;
          }

		//relase frame resource
		frame.release();
	}
}
 
void CameraStreamer::startMultiCapture()
{

	m_brun=true;
	VideoCapture *capture;
	thread *t;
	concurrent_queue<Mat> *q;
	for (int i = 0; i < camera_count; i++)
	{
		//Make VideoCapture instance
		if (!isUSBCamera){
			string url = camera_source[i];
			capture = new VideoCapture(url);
			cout << "Camera Setup: " << url << endl;
		}
		else{
			int idx = camera_index[i];
			capture = new VideoCapture(idx);
			cout << "Camera Setup: " << to_string(idx) << endl;
		}
	 
		//Put VideoCapture to the vector
		camera_capture.push_back(capture);
		//Make a queue instance
		q = new concurrent_queue<Mat>;
		 
		//Put queue to the vector
		frame_queue.push_back(q);
		 
		//Make thread instance
		t = new thread(&CameraStreamer::captureFrame, this, i);
		 
		//Put thread to the vector
		camera_thread.push_back(t);
		 
	}
}
 
void CameraStreamer::stopMultiCapture()
{
	m_brun=false;
	VideoCapture *cap;
	for (int i = 0; i < camera_count; i++) {
		cap = camera_capture[i];
		if (cap->isOpened()){
		//Relase VideoCapture resource
		cap->release();
		cout << "Capture " << i << " released" << endl;
		}

		thread *t=camera_thread[i];
	cout<<" ~join over===1"<<endl;
		t->join();
	cout<<" ~join over===2"<<endl;
		delete t;
		t=NULL;
		camera_thread[i]=NULL;

		delete cap;
		cap=NULL;
		camera_capture[i]=NULL;

		delete frame_queue[i];
		frame_queue[i]=NULL;
		
	}
}