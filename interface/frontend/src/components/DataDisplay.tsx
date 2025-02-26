interface DataDisplayProps {
    label: string;
    data: string | number;
}

const DataDisplay = ({label, data}: DataDisplayProps) => {
  return (
    <div className="mb-4">
        <h5 className="text-gray-400 text-xs">{label}</h5>
        <p className="font-bold text-2xl">{data}</p>
    </div>
  )
}

export default DataDisplay;
