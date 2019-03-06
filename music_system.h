#ifndef MUSIC_SYSTEM_H
#define MUSIC_SYSTEM_H

class music_system
{
  // user-accessible "public" interface
  public:
    void turnMusicsystemOn(void);
    void turnMusicsystemOff(void);
    void setSourceDVD(void);
    void setSourceAux(void);
    void setSourceTape(void);
    void sourceOneUp(void);
    void sourceOneDown(void);
    void volumeOneUp(void);
    void volumeOneDown(void);
    void setVolume(int);
    void setVolumeMute(void);

  // library-accessible "private" interface
  private:
};

#endif