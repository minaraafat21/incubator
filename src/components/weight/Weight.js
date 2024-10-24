// src/components/HeartBeat.js
import React from 'react';
import './Weight.css';

const Weight = ({ weight }) => {
  return (
    <div className="weight-card">
      <div>
        <h3>Weight</h3>
        <h4>{weight} kg</h4>
      </div>
      <div>
        <img src="./baby-weight.png" alt="Heart " width={90}/>
      </div>
    </div>
  );
};

export default Weight;
