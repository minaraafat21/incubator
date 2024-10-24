// src/components/HeartBeat.js
import React from 'react';
import './Humidity.css';

const Humidity = ({ Humidity }) => {
  return (
    <div className="Humidity-card">
      <div>
        <h2>Humidity</h2>
        <h3>{Humidity} %</h3>
      </div>
      <div>
        <img src="./humidity_6469293.png" alt="Heart " width={70}/>
      </div>
    </div>
  );
};

export default Humidity;
