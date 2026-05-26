#pragma once
#include <QObject>

class QTimer;

class GamepadHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit GamepadHandler(QObject *parent = nullptr);
    ~GamepadHandler();

    bool isConnected() const;

    Q_INVOKABLE void sendKey(int qtKey);

Q_SIGNALS:
    void aPressed();
    void bPressed();
    void xPressed();
    void yPressed();
    void selectPressed();
    void startPressed();
    void guidePressed();
    void dpadUp();
    void dpadDown();
    void dpadLeft();
    void dpadRight();
    void l1Pressed();
    void r1Pressed();
    void l2Pressed();
    void r2Pressed();
    void l3Pressed();
    void r3Pressed();
    void l3r3Pressed();
    void selectL2Pressed();
    void connectedChanged();

private:
#ifdef HAVE_SDL2
    bool m_connected = false;
    QTimer *m_pollTimer = nullptr;
    QTimer *m_axisRepeatTimer = nullptr;
    int m_leftX = 0, m_leftY = 0;
    int m_rightX = 0, m_rightY = 0;
    int m_axisDirLast = 0;
    bool m_selectHeld = false;
    bool m_l2WasPressed = false;
    bool m_r2WasPressed = false;
    bool m_l3Held = false;
    bool m_r3Held = false;
    static constexpr int kDeadzone = 8000;
    void pollEvents();
    int axisDirection() const;
    void emitAxisDir(int dir);
    void onAxisRepeat();
#endif
};
