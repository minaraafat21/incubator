// src/components/HeartBeat.js
import React from 'react';
import './heartBeat.css';

const HeartBeat = ({ heartBeat }) => {
  return (
    <div className="reading-card">
      <div>
        <h2>Heart rate</h2>
        <h3>{heartBeat} bpm</h3>
      </div>
      <div>
        <img src="./Vector_12.png" alt="Heart " />
      </div>
    </div>
  );
};

export default HeartBeat;
