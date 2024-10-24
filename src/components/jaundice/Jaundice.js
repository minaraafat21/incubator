// src/components/HeartBeat.js
import React from 'react';
import './Jaundice.css';

const Jaundice = ({ Jaundice }) => {
  if(Jaundice){
    return (
      <div className="Jaundice-card-yellow">
        <div>
          <h2>Jaundice detected</h2>
          {/* <h3>{Jaundice} </h3> */}
        </div>
        <div>
          <img src="./color-palette_3214398.png" alt="Heart " width={70}/>
        </div>
      </div>
    );


  }

  else{
  return (
    <div className="Jaundice-card">
      <div>
        <h2>Jaundice not detected</h2>
        {/* <h3>{Jaundice} </h3> */}
      </div>
      <div>
        <img src="./color-palette_3214398.png" alt="Heart " width={70}/>
      </div>
    </div>
  );
}};

export default Jaundice;
