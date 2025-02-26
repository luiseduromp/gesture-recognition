interface NetworkOutputProps {
    gesture: string;
    output: Record<string, string> | null;
}

const NetworkOutput = ({gesture, output}:NetworkOutputProps) => {
  return (
    <div className="mb-4">
        <p className="text-gray-400 text-xs">NETWORK OUTPUT</p>
        {output && Object.entries(output).map(([ges, prb]) => {
            return (
            <div key={ges} className="grid grid-cols-2 gap-2">
                <div className={` ${(ges === gesture) ? "text-purple-400 font-bold" : "text-neutral-300"}`}>{ges}</div>
                <div className={` ${(ges === gesture) ? "text-purple-400 font-bold" : "text-gray-400"}`}>{prb}</div>
            </div>               
            )}
        )}
    </div>
  )
}

export default NetworkOutput