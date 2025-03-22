# Radiance Smart Bin

Welcome to the Radiance Smart Bin project repository. This smart waste management system automates bin operations to improve efficiency and ensure timely waste disposal. It was developed by Radiance High School for the Robocode Fest 1.0 competition, where it secured 2nd place.

## Features

### 1. Automated Bin Opening & Closing

- **Motion Detection**: The bin automatically opens when a user approaches the bin and is detected within 30 cm.
- **Servo Motor Control**: A servo motor opens and closes the bin lid.

### 2. Bin Level Monitoring

- **Ultrasonic Sensors**: Measures the fill level inside the bin.
- **Full Bin Indicator**: Alerts when the bin is full using LEDs and a buzzer.

### 3. Alert System

- **Automated Notifications**: Displays the bin status:
  - **SMS Alerts**: Notifies the waste collection service (LAWMA) via SMS when the bin is full.
  - **Phone Calls**:  Initiates a phone call to LAWMA for immediate attention.
  
### 4. Real-time Monitoring

- The system continuously monitors waste levels and triggers alerts when necessary.

> The components used for this project are listed [**here**](./components.md): `components.md`

## Code Structure

The project consists of a single Arduino script handling bin automation and monitoring:

- Main Code: `radiance-smart-bin.ino`
- Functions:
  - `setup()` - Initializes the serial communication, GSM module, and pin configurations.
  - `loop()` - Continuously monitors sensor readings and controls the bin operations.
  - `checkDistance(int trigPin, int echoPin)` - Measures distance using ultrasonic sensors.
  - `call(String mobileNumber)`: Places a call to a specified number via the GSM module.
  - `sendSMS(String mobileNumber, String msgBody)`: Sends an SMS notification.
  - `readResponse()`: Reads responses from the GSM module to ensure proper communication.


## How to Use

1. Clone the repository:

```sh
git clone https://github.com/emmanueldev247/radiance-smart-bin.git
```

2. Connect the components as per the provided [**Circuit Diagram**](./radiance-smart-bin-circuit-diagram.jpg).
3. Ensure necessary libraries are installed.
    - `Servo.h` (for servo motor control)
    - `SoftwareSerial.h` (for GSM module communication)
4. Upload the code to your Arduino board.
5. Power the system and observe its functionality.

## Contributing

Contributions are welcome! Feel free to create issues, suggest new features, or open pull requests to improve the Radiance Smart Bin.

> Enjoy building a cleaner and smarter waste management system with Radiance Smart Bin!

## Authors

<details>
    <summary>Emmanuel Ademola</summary>
    <ul>
    <li><a href="https://www.github.com/emmanueldev247">Github</a></li>
    <li><a href="https://www.twitter.com/emmanueldev247">Twitter</a></li>
    <li><a href="mailto:mailemmydee@gmail.com">E-mail</a></li>
    <li><a href="https://emmanueldev247.publicvm.com">Portfolio</a></li>
    </ul>
</details>
