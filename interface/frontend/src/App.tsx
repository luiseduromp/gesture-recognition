import { useEffect, useState, useRef } from 'react'
import Spline from '@splinetool/react-spline';

import DataDisplay from './components/DataDisplay';
import NetworkOutput from './components/NetworkOutput';


import './App.css'

interface GestureData {
  type: string
  message: string | null
  predicted: string | null;
  prob: string | null;
  time: string | null;
  output: Record<string, string> | null;
}

enum Gesture {
  STILL = '',
  WAVE = 'wave',
  SWIPE_LEFT = 'swipe_left',
  SWIPE_RIGHT = 'swipe_right',
  SWIPE_UP = 'swipe_up',
  SWIPE_DOWN = 'swipe_down',
  STOP = 'stop',
  ROLL = 'roll'
}

const gestureMap = {
  'still': 'n',
  'wave': 'w',
  'swipe_left': 'ArrowLeft',
  'swipe_right': 'ArrowRight',
  'swipe_up': 'ArrowUp',
  'swipe_down': 'ArrowDown',
  'stop': 's',
  'roll': 'r'
}

const simulateKeyPress = (key: string) => {
  const event = new KeyboardEvent('keydown', { key: key });
  console.log('SIMULATE KEY PRESS: ' + key);
  document.dispatchEvent(event);
  setTimeout(() => {
    const event = new KeyboardEvent('keyup', { key: key });
    document.dispatchEvent(event);
  }, 50);
}


const App = () => {
  const [data, setData] = useState<GestureData | null>(null);
  const [gesture, setGesture] = useState<Gesture>(Gesture.STILL);

  const [maxTime, setMaxTime] = useState<number>(0);
  const [minTime, setMinTime] = useState<number>(1000);

  const currentTime = useRef<number>(0);


  useEffect(() => {
    const ws = new WebSocket('ws://localhost:8000/ws/data');

    ws.onmessage = (event) => {
      try {
        const receivedData = JSON.parse(event.data); 
        if(receivedData.type === 'raw'){
          setData(receivedData);
        } else if(receivedData.type === 'proc'){
          setGesture(receivedData.predicted);
        }

        if(receivedData.time){
          currentTime.current = parseInt(receivedData.time);
          if(currentTime.current > maxTime){
            setMaxTime(currentTime.current);
          }
          if(currentTime.current < minTime){
            setMinTime(currentTime.current);
          }
        }
        
      } catch(err) {
        console.log('Error' + err);
      }
    }

    ws.onerror = (event) => {
      console.log('Websocket Error: ' + event);
    }

    ws.onclose = (event) => {
      console.log('Websocket Connection Closed: ' + event);
    }

    return () => {
      ws.close();
    }
  }, [])


  useEffect(() => {
    simulateKeyPress(gestureMap[gesture as keyof typeof gestureMap]);
    if (gesture) {
      const timeout = setTimeout(() => {
        setGesture(Gesture.STILL);
      }, 2000);
      return () => clearTimeout(timeout);
    }
  }, [gesture])





  return (
      <div className="flex flex-row h-screen bg-black">
        <aside className="relative basis-1/4 xl:basis-1/6 px-4 py-4 backdrop-blur-lg bg-inherit">

          <div className="mb-6 ps-4">
            <img src="/logoUPC.png" className="w-48 mb-2" />
            <p className="text-xs mb-1">Master's Final Project</p>
            <h3 className="text-sm font-bold">Gesture Recognition App</h3>
          </div>

          <div className="ps-4 mb-8">
            <h5 className="text-sm text-gray-400 font-bold mb-4">REAL-TIME DATA</h5>

            <DataDisplay label="PREDICTED" data={data?.predicted || 'No gesture detected'} />
            <DataDisplay label="PROBABILITY" data={data?.prob || '0'} />
            <DataDisplay label="TIME" data={data?.time || 'NA'} />
            <NetworkOutput gesture={gesture} output={data?.output || {}} />
          </div>

          <div className="ps-4 mb-4">
            <h5 className="text-sm text-gray-400 font-bold">PROCESSED DATA</h5>
            <p className="font-bold text-purple-400 text-3xl">{gesture}</p>
          </div>

          <div className="absolute bottom-0 left-0 right-0 p-4 text-xs text-center text-gray-400">
            <p className="mb-1">Luis Eduardo Romero Paredes</p>
            <p className="font-bold">2025 - UPC EPSEVG</p>
          </div>

        </aside>

        <section className="relative basis-3/4 xl:basis-5/6 bg-black">

          <Spline scene="https://prod.spline.design/m2TsWH6rruoFXQLp/scene.splinecode" />

          <div className="absolute mb-4 ps-4 bottom-24 left-0 right-0">
            <div className={`${gesture ? "w-96 text-center mx-auto text-4xl 2xl:text-6xl px-6 py-4 backdrop-blur-md rounded-3xl font-bold text-purple-400" : ""}`}>
              {gesture}
            </div>
          </div>

          <div className="absolute bottom-0 left-0 right-0 px-4 py-4 text-center text-[0.6rem] text-gray-400 backdrop-blur-lg">
            <img src="/tfm_auspicios.png" alt="" className="h-6 mx-auto mb-4" />
            <p>
              Prroject financed and supported by the "Siemens Energy AI Chair: Energy Sustainability for a Decarbonized Society 5.0"; 
              funded by the Secretary of <br /> State for Digitalization and Artificial Intelligence through the ENIA 2022 Chairs call, 
              and co-funded by the European Union-Next Generation EU.
            </p>
          </div>
          
        </section>

      </div>

  )
}

export default App
