// src/components/HeartBeat.js
import React from 'react';
import './Sound.css';

const Sound = ({ Sound }) => {
  return (
    <div className="Sound-card">
      <div>
        <h3>Sound</h3>
        <h4>{Sound} dB</h4>
      </div>
      <div>
        <img src="./sound-waves.png" alt="Heart " width={90}/>
      </div>
    </div>
  );
};

export default Sound;
