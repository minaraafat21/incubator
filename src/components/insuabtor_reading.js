// src/components/IncubatorReadings.js
import React, { useState, useEffect } from 'react';
import axios from 'axios';
import './reading.css';
import HeartBeat from './heartBeat/heartBeat';
import Weight from './weight/Weight';
import Temp from './temp/Temp';
import Humidity from './Humidity/Humidity';
import Jaundice from './jaundice/Jaundice';
import Sound from './Sound/Sound';

const IncubatorReadings = () => {
  const [readings, setReadings] = useState({
    temperature: null,
    humidity: null,
    jaundice: null,
    noiseLevel: null,
    weight: null,
    heartRate: null,
  });
  // readings.jaundice = 1;
  if (readings.temperature > 37) {
          alert('Warning: Temperature exceeds 37°C!');
        }
  const ESP32_IP_ADDRESS = '192.168.43.126';

  useEffect(() => {
    const fetchReadings = async () => {
      try {
        const response = await axios.get(`http://${ESP32_IP_ADDRESS}/readings`);

        console.log('dataa: ', response.data);

        setReadings({
          temperature: response.data.temperature,
          humidity: response.data.humidity,
          jaundice: response.data.jaundice,
          noiseLevel: response.data.noiseLevel,
          weight: response.data.weight,
          heartRate: response.data.heartRate,
        });

       

        console.log('readings: ', response.data);
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };

    // Polling every 2 seconds
    const interval = setInterval(fetchReadings, 2000);


    return () => clearInterval(interval);
  }, []); // Empty dependency array to run effect only on mount

  return (
    <div className='parent'>
      <HeartBeat heartBeat={readings.heartRate} />
      <div className="two-card">
        <Temp Temp={readings.temperature} />
        <Humidity Humidity={readings.humidity} />
      </div>
      <Jaundice Jaundice={readings.jaundice} />
      <div className="two-card">
        <Weight weight={readings.weight} />
        <Sound Sound={readings.noiseLevel} />
      </div>
    </div>
  );
};

export default IncubatorReadings;
