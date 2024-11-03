// src/components/HeartBeat.js
import React from 'react';
import './Temp.css';

const Temp = ({ Temp }) => {
  if (Temp > 30) {
    return (
      <div className="temp-card-red">
        <div>
          <h2>temp</h2>
          <h3>{Temp} </h3>
        </div>
        <div>
          <img src="./forecast_15482051.png" alt="Heart " width={50}/>
        </div>
      </div>
    );
  }
  else{

  return (
    <div className="temp-card">
      <div>
        <h2>temp</h2>
        <h3>{Temp} </h3>
      </div>
      <div>
        <img src="./forecast_15482051.png" alt="Heart " width={50}/>
      </div>
    </div>
  );
};
};
export default Temp;
