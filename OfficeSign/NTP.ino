/*
 * Based on: Time library's Time_NTP.pde
 */
 
#include <Time.h> 
#include <EthernetUdp.h>
#include <SPI.h>

#define NTP_PACKET_SIZE 48 // NTP time is in the first 48 bytes of message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
EthernetUDP Udp;

void setupNTP() {
  Udp.begin(8888);
}

time_t getNtpTime() {
  
  while (Udp.parsePacket() > 0) ; // discard any previously received packets

  sendNTPpacket();
  
  while (Udp.parsePacket() < NTP_PACKET_SIZE)
    delay(1500);
 
  Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer

  unsigned long secsSince1900;
  // convert four bytes starting at location 40 to a long integer
  secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
  secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
  secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
  secsSince1900 |= (unsigned long)packetBuffer[43];
  
  return timezone.toLocal(secsSince1900 - 2208988800UL);
}

// send an NTP request to the time server at the given address
void sendNTPpacket()
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(TIME_SERVER, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

