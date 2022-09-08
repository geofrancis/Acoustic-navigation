


#define trigPin 6        //Ultrasound modules wiring R=Right L=Left the other one is the middle
#define echoPin 7
#define trigPinR 8
#define echoPinR 9
#define trigPinL 10
#define echoPinL 11
#define Maxdistone  200  //Maximum distance 20cm
#define Maxdispulse 350  //Maximum distance 20cm
#define Lbuzz 12
#define Rbuzz 13

long duration; 
int distance;


int buzzer=7;
int Lfreq = 1;
int Rfreq = 1;
int Lpulse = 1;
int Rpulse = 1;

void setup() {
     pinMode(trigPin, OUTPUT);       //Pinmodes of the HC-SR04 and starting the displays
     pinMode(echoPin, INPUT);
     pinMode(trigPinR, OUTPUT);
     pinMode(echoPinR, INPUT); 
     pinMode(trigPinL, OUTPUT);
     pinMode(echoPinL, INPUT); 
     pinMode(Rbuzz,  OUTPUT);  //setting up buzzer pin as output
     pinMode(Lbuzz,  OUTPUT);  //setting up buzzer pin as output
}

void loop() {

    int distanceM = CDistance(trigPin,echoPin);      //Calculating all the distances by calling the function below
    int distanceR = CDistance(trigPinR,echoPinR);
    int distanceL = CDistance(trigPinL,echoPinL);

    int R=min(distanceM,distanceR);                //We have two displays R and L, first we take the minimum distance between M/R and M/L
    int L=min(distanceM,distanceL);

    if(R>0 && R < Maxdistone||R<=0){      //Range of distance
      Rfreq=map(R,0,Maxdistone,500,10000);      //Scaling the disntace from 0-20 to 0-7
      tone(Rbuzz, Rfreq);
    }
   
    if(R>Maxdistone && R < Maxdispulse||R<=0){
    Rpulse=map(R,Maxdistone,Maxdispulse,100,800);
     tone(Rbuzz, Rfreq, Rpulse);
    }
     else(R> Maxdispulse); {                          //We're safe and the displays always shows there's enough space
   noTone (Rbuzz);
}
    
     if(L>0 && L < Maxdistone||L<=0){      //Range of distance
      Lfreq=map(L,0,Maxdistone,500,10000);      //Scaling the disntace from 0-20 to 0-7
      tone(Lbuzz, Lfreq, Lpulse);
    }
    if(L> Maxdispulse)                           //We're safe and the displays always shows there's enough space
   noTone (Lbuzz);
   
    if(L>Maxdistone && L < Maxdispulse||L<=0){
    Lpulse=map(L,Maxdistone,Maxdispulse,100,800);
    }
     if(L> Maxdispulse)                           //We're safe and the displays always shows there's enough space
   noTone (Lbuzz);
     delay(1000);
}

int CDistance(int a, int b){             //Calculating distance function, it takes two arguments (Trigger and Echo) and it executes the usual process of the HC-SR04
     digitalWrite(a, LOW); 
     delayMicroseconds(2);       
     digitalWrite(a, HIGH);
     delayMicroseconds(10);      
     digitalWrite(a, LOW); 
     duration = pulseIn(b, HIGH); 
     distance = duration*(0.034/2); 
     return distance;                  //Return the distance calculated
}


