//*****************************************//
//  midiout.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI output.
//
//*****************************************//

#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <QString>
#include <sstream>
#include "RtMidi.h"

// Platform-dependent sleep routines.
#if defined(WIN32)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
bool chooseMidiPort( RtMidiOut *rtmidi );

struct notas {
    unsigned short canal;
    unsigned short nota;
    unsigned short vel;
    unsigned int tempo;
};

int main( void )
{
  RtMidiOut *midiout = 0;
  std::vector<unsigned char> message;
  std::string notes = "PRUEBA EN MaYuS A Ber QUE tal SUENA esto hola que tal jejejeje quesaweaaaaasklkdjadcrnsjdoemaskdjeoidd";
  std::vector<struct notas> cancion;
  QFile file(":/midi/fur_elise.csv");
  char buffer[200];
  unsigned int tick = 0;

  // RtMidiOut constructor
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  // Call function to select port.
  try {
    if ( chooseMidiPort( midiout ) == false ) goto cleanup;
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    goto cleanup;
  }

  //abro el archivito de sonido
  //file.open("fur_elise.csv");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      std::cout << "error al abrir" << std::endl;
      goto cleanup;
  }

  message.resize(3);

  while (!file.atEnd()) {

    file.readLine(buffer, 199);
    QString line(buffer);
    QStringList param = line.split(',');
    struct notas aux;

    if (param.size() == 1) continue;
    if (param.at(2).trimmed() == "Program_c") {
        message[0] = 0xC0 + param.at(3).trimmed().toInt();
        message[1] = param.at(4).trimmed().toInt();
        midiout->sendMessage(&message);
    } else if (param.at(2).trimmed() == "Control_c") {
        message[0] = 0xB0 + param.at(3).trimmed().toInt();
        message[1] = param.at(4).trimmed().toInt();
        message[2] = param.at(5).trimmed().toInt();
    } else if (param.at(2).trimmed() == "Note_on_c" || param.at(2).trimmed() == "Note_off_c") {
        aux.tempo = param.at(1).trimmed().toInt();
        aux.canal = param.at(3).trimmed().toUShort();
        aux.nota = param.at(4).trimmed().toUShort();
        aux.vel = (param.at(2).trimmed() == "Note_off_c") ? 0 : param.at(5).trimmed().toUShort();
        cancion.push_back(aux);
    } else if (param.at(2).trimmed() == "End_track") {
    }
    //std::cout << "line size: " << line.size() << std::endl;
    //std::cout << "trimmed 2param: " << param.at(2).trimmed().toStdString() << std::endl;
  }

  //std::cout << cancion.size() << std::endl;


  // Send out a series of MIDI messages.

  // Program change: 192, 5
  /*message.push_back( 192 );
  message.push_back( 35 );
  midiout->sendMessage( &message );

  SLEEP( 500 );
*/
  message.resize(0);
  //Reinicio el synth en modo GS
  //F0H 41H, 10H, 42H, 12H, 40H, 00H, 7FH, 00H, 41H, F7H
  message.push_back(0xF0);
  message.push_back(0x41);
  message.push_back(0x00);
  message.push_back(0x42);
  message.push_back(0x12);
  message.push_back(0x40);
  message.push_back(0x00);
  message.push_back(0x7f);
  message.push_back(0x00);
  message.push_back(0x41);
  message.push_back(0xF7);
  midiout->sendMessage(&message);

  SLEEP(50);

  message.resize(3);

  message[0] = 0xF1;
  message[1] = 60;
  midiout->sendMessage( &message );

  // Control Change: 176, 7, 100 (volume)
  message[0] = 176;
  message[1] = 7;
  message[2] = 100;
  midiout->sendMessage( &message );

  message[0] = 0xB0;
  message[1] = 0x00;
  message[2] = 24;
  midiout->sendMessage(&message);
  message[0] = 0xB0;
  message[1] = 0x20;
  message[2] = 0;
  midiout->sendMessage(&message);
  message[0] = 0xC0;
  message[1] = 4;
  message[2] = 0;
  midiout->sendMessage(&message);

  message[0] = 0xB1;
  message[1] = 0x00;
  message[2] = 24;
  midiout->sendMessage(&message);
  message[0] = 0xB1;
  message[1] = 0x20;
  message[2] = 0;
  midiout->sendMessage(&message);
  message[0] = 0xC1;
  message[1] = 4;
  message[2] = 0;
  midiout->sendMessage(&message);

  //notes
  //message.resize(2);
  /*for (unsigned int i=0; i < notes.length(); i++) {
      message[0] = 0x90;
      message[1] = (uint8_t)notes[i];
      message[2] = 90;
      //std::cout << "msg val: " << (uint8_t)message[1] << std::endl;
      midiout->sendMessage(&message);
      SLEEP(100);
      message[0] = 0x90;
      message[1] = (uint8_t)notes[i];
      message[2] = 0;
      midiout->sendMessage(&message);
  }
  message.resize(3);*/
  tick = cancion[0].tempo;
  for (unsigned int i=0; i<cancion.size(); i++) {
      message[0] = (uint8_t) 0x90 + cancion[i].canal;
      message[1] = (uint8_t) cancion[i].nota;
      message[2] = (uint8_t) cancion[i].vel;
      midiout->sendMessage(&message);
      if (cancion[i].tempo - tick) {
          SLEEP((cancion[i].tempo - tick)/3);
      }
      std::cout << "nota: " << cancion[i].nota << "vel: " << cancion[i].vel << "canal: " << cancion[i].canal << "tempo" << cancion[i].tempo << std::endl;
      tick = cancion[i].tempo;
  }


  // Control Change: 176, 7, 40
  message[0] = 176;
  message[1] = 7;
  message[2] = 40;
  midiout->sendMessage( &message );

  SLEEP( 500 );

  // Sysex: 240, 67, 4, 3, 2, 247
  message[0] = 240;
  message[1] = 67;
  message[2] = 4;
  message.push_back( 3 );
  message.push_back( 2 );
  message.push_back( 247 );
  midiout->sendMessage( &message );

  // Clean up
 cleanup:
  delete midiout;
  file.close();

  return 0;
}

bool chooseMidiPort( RtMidiOut *rtmidi )
{
  std::cout << "\nWould you like to open a virtual output port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
  }

  std::cout << "\n";
  rtmidi->openPort( i );

  return true;
}
