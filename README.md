# 2022_Robot_A

API for comm.h :
 Commande         | ROS              | Dir   |   Serial  | Etat
| :-------------: |:-------------:|:---:|:-------------:| :-------------:|
| Stop      | cmd_vel(0) ou autre ? |                > |        s |
| Gain PID  | pid |                > |        g {pid_id, kp, ki, kd}      | To update
| Vitesse      | cmd_vel(m/s, rad/s) |                > |        v {vx} {vomega} |
| Declare actuator      | actuator |                < |        d | To specify
| Cmd AX12      | actuator |                > |        a a{ID} {value}  |
| Cmd pompe | cmd_vel(0) ou autre ? |                > |        a p  |
| Cmd electrov| cmd_vel(0) ou autre ? |   > |        a e |
| Cmd | cmd_vel(0) ou autre ? |         > |  a s |
| Cmd | cmd_vel(0) ou autre ? |   > |        a t |
| Cmd test | cmd_vel(0) ou autre ? |    **<** | r x y theta speed omega |
| spam value |  ??? | < | a {ID}


Actuator topic :
Std_msg header
Origin (raspy or stm32)
type (write or read or spam)
value (0,360,...)
Unit (rad, m/s, ...)