#include <node.h>

//TODO Calibrate to real glove output values.
#define POINTER_CURLED_HALF_CURLED_CUTOFF 0x555
#define POINTER_HALF_CURLED_EXTENDED_CUTTOFF 0xaaa
#define MIDDLE_CURLED_HALF_CURLED_CUTOFF 0x555
#define MIDDLE_HALF_CURLED_EXTENDED_CUTTOFF 0xaaa
#define INDEX_CURLED_HALF_CURLED_CUTOFF 0x555
#define INDEX_HALF_CURLED_EXTENDED_CUTTOFF 0xaaa
#define PINKY_CURLED_HALF_CURLED_CUTOFF 0x555
#define PINKY_HALF_CURLED_EXTENDED_CUTTOFF 0xaaa
#define THUMB_CURLED_HALF_CURLED_CUTOFF 0x555
#define THUMB_HALF_CURLED_EXTENDED_CUTTOFF 0xaaa

typedef enum state 
{
  ZERO, 	
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  PLUS //some operation ... to be confirmed
} state;

typedef enum fingerState 
{
	extended,
	half_curled, //determine other states
	full_curled,
} fingerState;


namespace CATbackend {   

//void Method (oldState, count,  data)
	void Method(const v8::Arguments& args) 
	{
		v8::Handle<v8::Object> results = v8::Object::New();
		v8::Handle<v8::Array>  data_list = v8::Handle<v8::Array>::Cast(args[2]);

		results->Set(v8::Handle<v8::Value>::Cast(v8::String::New("count")), args[1]);
		results->Set(v8::Handle<v8::Value>::Cast(v8::String::New("oldState")), args[0]);

		while (true)
		 {
		 	//get data from server

			fingerState pointerFinger;  //initialize with glove data values for each finger
			fingerState pinkyFinger;
			fingerState thumbFinger;
			fingerState indexFinger;
			fingerState middleFinger;

			int pointerFingerData = data_list->CloneElementAt(1)->Int32Value();
			int pinkyFingerData = data_list->CloneElementAt(4)->Int32Value();
			int thumbFingerData = data_list->CloneElementAt(0)->Int32Value();
			int indexFingerData = data_list->CloneElementAt(3)->Int32Value();
			int middleFingerData = data_list->CloneElementAt(2)->Int32Value();


			//substitute question marks with values that are applicable with the data

			//pointer finger
			if (pointerFingerData < POINTER_CURLED_HALF_CURLED_CUTOFF)
			{
				pointerFinger = full_curled;
			
			}
			else if (pointerFingerData < POINTER_HALF_CURLED_EXTEDED_CUTOFF)
			{
				pointerFinger = half_curled;
			}
			else
			{
				pointerFinger = extended;
			}


			//pinky finger
			if (pinkyFingerData < PINKY_CURLED_HALF_CURLED_CUTOFF)
			{
				pinkyFinger = full_curled;
			
			}
			else if (pinkyFingerData < PINKY_HALF_CURLED_EXTEDED_CUTOFF)
			{
				pinkyFinger = half_curled;
			}
			else
			{
				pinkyFinger = extended;
			}


			//thumb finger
			if (thumbFingerData < THUMB_CURLED_HALF_CURLED_CUTOFF)
			{
				pinkyFinger = full_curled;
			
			}
			else if (thumbFingerData < THUMB_HALF_CURLED_EXTEDED_CUTOFF)
			{
				thumbFinger = half_curled;
			}
			else
			{
				thumbFinger= extended;
			}


			//middle finger
			if (middleFingerData < MIDDLE_CURLED_HALF_CURLED_CUTOFF)
			{
				middleFinger = full_curled;
			
			}
			else if (middleFingerData < MIDDLE_HALF_CURLED_EXTEDED_CUTOFF)
			{
				middleFinger = half_curled;
			}
			else
			{
				middleFinger = extended;
			}


			//index finger
			if (indexFingerData < INDEX_CURLED_HALF_CURLED_CUTOFF)
			{
				indexFinger = full_curled;
			
			}
			else if (indexFingerData < INDEX_HALF_CURLED_EXTEDED_CUTOFF)
			{
				indexFinger = half_curled;
			}
			else
			{
				indexFinger = extended;
			}

			//sign indentifier

			if (pointerFinger == half_curled && pinkyFinger == half_curled && indexFinger == half_curled && thumbFinger == half_curled && middleFinger == half_curled)
			{
				returnValues.handState = ZERO;
			}

			if (pointerFinger == extended && pinkyFinger == full_curled && indexFinger == full_curled && thumbFinger == full_curled && middleFinger == full_curled)
			{
				returnValues.handState = ONE;	
			}

			if (pointerFinger == extended && pinkyFinger == full_curled && indexFinger == full_curled && thumbFinger == full_curled && middleFinger == extended)
			{
				returnValues.handState = TWO;	
			}

			if (pointerFinger == extended && pinkyFinger == full_curled && indexFinger == full_curled && thumbFinger == extended && middleFinger == extended)
			{
				returnValues.handState = THREE;
			}

			if (pointerFinger == extended && pinkyFinger == extended && indexFinger == extended && thumbFinger == full_curled && middleFinger == extended)
			{
				returnValues.handState = FOUR;
			}

			if (pointerFinger == extended && pinkyFinger == extended && indexFinger == extended && thumbFinger == extended && middleFinger == extended)
			{
				returnValues.handState = FIVE;
			}

			if (pointerFinger == extended && pinkyFinger == full_curled && indexFinger == extended && thumbFinger == full_curled && middleFinger == extended)
			{
				returnValues.handState = SIX;
			}

			if (pointerFinger == extended && pinkyFinger == extended && indexFinger == full_curled && thumbFinger == full_curled && middleFinger == extended)
			{
				returnValues.handState = SEVEN;
			}

			if (pointerFinger == extended && pinkyFinger == extended && indexFinger == extended && thumbFinger == full_curled && middleFinger == full_curled)
			{
				returnValues.handState = EIGHT;
			}

			if (pointerFinger == full_curled && pinkyFinger == extended && indexFinger == extended && thumbFinger == full_curled && middleFinger == extended)
			{
				returnValues.handState = NINE;
			}


			if (returnValues.handState == result ->Get(v8::String::NewSymbol("oldState")))
			{
				//returnValues.count++;
				results->Set(v8::String::NewSymbol("count"), result->Get(v8::String::NewSymbol("count") + 1));

			}

			else
			{
				results->Set(v8::String::NewSymbol("count"), 0);

			}

			if (result->Get("count") == 10)
			{
				args.GetReturnValue().Set(result);
			}

			results->Set(v8::String::NewSymbol("oldState"), handState);

			args.GetReturnValue().Set(result);


		 }
	}

	void init(v8::Local<v8::Object> exports) 
	{
		NODE_SET_METHOD(exports, , Method);
	} 


	NODE_MODULE(NODE_GYP_MODULE_NAME, init)
}











