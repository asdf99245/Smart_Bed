
# <b>LG WEBOS project: Smart Bed</b>

A project using <b>Web OS LUNA AI voice service </b>

solution of project is <b>smart bed system</b>. we say some commands and arduino react.

## System Architecture

<img width="834" alt="architecture" src="https://user-images.githubusercontent.com/39851220/167302354-ee7bf210-7c2a-476b-b2a0-40992aef64db.png">

IFTTT is the service that makes easy to generate custom commands which google assistant don't recognize. We used this service to make our own commands.

In short,
* Say commands which we made using IFTTT to microphone.
* webOS application sends commands to google assistant server. Then server will response to application.
* webOS application sends specific JSON data to Arduino using HTTP request based on response.
* Arduino controls right actuators depending on the data.

## Usage or Scenario

1. Execute webOS and turn on <b>Smart_Bed</b> .

2. Click <b>start</b> button, then LUNA AI service will ready to receive your voice.

3. Say some commands we made. For example, <b>say " I want to read"</b>. Your bed will <b>fold up.</b>

<img width="834" alt="Scenario" src="https://user-images.githubusercontent.com/39851220/167302302-0ebf9be5-485b-4ab5-9599-2a57543e54b4.png">

