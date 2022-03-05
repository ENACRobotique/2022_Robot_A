#pragma once

class TestHardware
{
private:
    /* data */
public:
    TestHardware(float seconds_interval);
    ~TestHardware();
    virtual void launch_test();
    virtual void execute_test();
};

