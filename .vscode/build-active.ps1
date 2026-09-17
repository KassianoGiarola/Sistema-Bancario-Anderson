param(
    [Parameter(Mandatory = $true)]
    [string]$SourceFile,

    [Parameter(Mandatory = $true)]
    [string]$WorkspaceFolder,

    [switch]$Run
)

$ErrorActionPreference = "Stop"

$mingwBin = "C:\msys64\ucrt64\bin"
$compiler = Join-Path $mingwBin "g++.exe"

if (-not (Test-Path -LiteralPath $compiler)) {
    Write-Error "g++.exe nao encontrado em $compiler"
    exit 1
}

$allowedExtensions = @(".cpp", ".cc", ".cxx", ".c++")
$sourceExtension = [System.IO.Path]::GetExtension($SourceFile).ToLowerInvariant()
if ($allowedExtensions -notcontains $sourceExtension) {
    Write-Error "Abra um arquivo C++ (.cpp, .cc, .cxx ou .c++) antes de compilar. Arquivo ativo: $SourceFile"
    exit 1
}

$env:PATH = "$mingwBin;$env:PATH"

$outputDir = Join-Path $WorkspaceFolder "build\Debug"
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null

$outputExe = Join-Path $outputDir "outDebug.exe"
$outputCompat = Join-Path $outputDir "outDebug"

Write-Host "Compilando $SourceFile"
& $compiler -Wall -Wextra -Wpedantic -std=c++17 -g $SourceFile -o $outputExe
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Copy-Item -Path $outputExe -Destination $outputCompat -Force
Write-Host "Executavel gerado em $outputExe"

if ($Run) {
    & $outputExe
    exit $LASTEXITCODE
}

exit 0
