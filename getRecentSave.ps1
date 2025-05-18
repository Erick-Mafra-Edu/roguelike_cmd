# Define a URL bruta do GitHub (raw)
$rawUrl = "https://raw.githubusercontent.com/Erick-Mafra-Edu/roguelike_cmd/MundialSave/gameSave.save"

# Caminho local onde o arquivo será salvo
$outputPath = "gameSave.save"

# Baixar com wget (alias de Invoke-WebRequest no PowerShell)
wget $rawUrl -OutFile $outputPath
