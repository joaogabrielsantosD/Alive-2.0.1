#include "tickerISR.h"

bool Print_in_serial = false;
Ticker ticker1Hz,
       ticker10Hz,
       ticker20Hz;

void setup_ticker()
{
  do 
  {
    Serial.println("Check the PID support...");
  } while(checkPID());
  
  ticker1Hz.attach(1.0, PIDs_1hz);
  ticker10Hz.attach(2.0, PIDs_10hz);
  //ticker20Hz.attach(3.0, PIDs_20hz);
}

bool checkPID()
{
  // Flag to check if you received the PID support message
  bool check_receive_pid = false;
  unsigned char Data[8] = {0x04, 0x01, 0x00/*=ID*/, 0x00, 0x00, 0x00, 0x00, 0x00};

  for(int i = 1; i < 5; i++)
  {
    Serial.printf("Trying to send PID%d support, please turn on the car electronics\r\n", i);
    check_receive_pid = false;
    
    while(!check_receive_pid)
    {
      if(i==1)
      {
        Data[2] = PIDsupported1;
        
        while(!checkReceive())
        {
          if(send_msg(Data) && Print_in_serial) debug_print(Data);
          vTaskDelay(1000);          
        }
        MsgRec_CANroutine();
        check_receive_pid = true;
      }

      if(i==2)
      {
        Data[2] = PIDsupported2;
        if(send_msg(Data) && Print_in_serial) debug_print(Data);
        while(!checkReceive()) vTaskDelay(1);
        MsgRec_CANroutine();
        check_receive_pid = true;
      }

      if(i==3)
      {
        Data[2] = PIDsupported3;
        if(send_msg(Data) && Print_in_serial) debug_print(Data);
        while(!checkReceive()) vTaskDelay(1);
        MsgRec_CANroutine();
        check_receive_pid = true;
      }

      if(i==4)
      {
        Data[2] = PIDsupported4;
        if(send_msg(Data) && Print_in_serial) debug_print(Data);
        while(!checkReceive()) vTaskDelay(1);
        MsgRec_CANroutine();
        check_receive_pid = true;
      }

      vTaskDelay(1);
    }

    if((i+1)==5) break;
  }

  return false;
}

void PIDs_1hz()
{
  insert(DistanceTraveled_ST);
  insert(EngineRPM_ST);
}

void PIDs_10hz()
{
  insert(VehicleSpeed_ST);
  insert(FuelLevel_ST);
  insert(EngineCoolant_ST);  
}

void PIDs_20hz()
{
  
}
