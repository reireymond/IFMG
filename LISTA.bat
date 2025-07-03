@echo off
chcp 1252 > nul
setlocal enabledelayedexpansion

:: Título
echo   ¦¦¦¦¦¦ ¦¦¦¦¦¦  ¦¦  ¦¦¦¦¦  ¦¦¦¦¦¦   ¦¦¦¦¦¦  ¦¦¦¦¦¦      ¦¦¦¦¦¦  ¦¦¦¦¦¦¦     ¦¦      ¦¦ ¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦  ¦¦¦¦¦ 
echo  ¦¦      ¦¦   ¦¦ ¦¦ ¦¦   ¦¦ ¦¦   ¦¦ ¦¦    ¦¦ ¦¦   ¦¦     ¦¦   ¦¦ ¦¦          ¦¦      ¦¦ ¦¦         ¦¦    ¦¦   ¦¦ 
echo  ¦¦      ¦¦¦¦¦¦  ¦¦ ¦¦¦¦¦¦¦ ¦¦   ¦¦ ¦¦    ¦¦ ¦¦¦¦¦¦      ¦¦   ¦¦ ¦¦¦¦¦       ¦¦      ¦¦ ¦¦¦¦¦¦¦    ¦¦    ¦¦¦¦¦¦¦ 
echo  ¦¦      ¦¦   ¦¦ ¦¦ ¦¦   ¦¦ ¦¦   ¦¦ ¦¦    ¦¦ ¦¦   ¦¦     ¦¦   ¦¦ ¦¦          ¦¦      ¦¦      ¦¦    ¦¦    ¦¦   ¦¦ 
echo   ¦¦¦¦¦¦ ¦¦   ¦¦ ¦¦ ¦¦   ¦¦ ¦¦¦¦¦¦   ¦¦¦¦¦¦  ¦¦   ¦¦     ¦¦¦¦¦¦  ¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦ ¦¦ ¦¦¦¦¦¦¦    ¦¦    ¦¦   ¦¦ 
echo.

:: Entrar com o número do capítulo
set /p CAPITULO=Digite o numero do capitulo (ex: 08): 

:: Entrar com o nome completo
set /p NOME=Digite o nome e sobrenome: 

:: Formatar nome (substituir espaços por "_")
set "NOME_FORMATADO=%NOME: =_%"
set "PASTA_CAP=Cap%CAPITULO%_%NOME_FORMATADO%"
echo.

:: Criar a pasta principal e subpastas
if not exist "%PASTA_CAP%" mkdir "%PASTA_CAP%"
if not exist "%PASTA_CAP%\Propostos" mkdir "%PASTA_CAP%\Propostos"
if not exist "%PASTA_CAP%\Resolvidos" mkdir "%PASTA_CAP%\Resolvidos"

:: Gerar arquivos PROPOSTOS
for /L %%i in (1,1,25) do (
    if %%i LSS 10 (
        set "num=0%%i"
    ) else (
        set "num=%%i"
    )
    
    (
        echo //Atividade Propostos !num! - Capítulo %CAPITULO%
        echo #include ^<stdio.h^>
        echo.
        echo int main^(^)
        echo {
        echo.
        echo     return 0;
        echo }
    ) > "%PASTA_CAP%\Propostos\Prop!num!_Cap%CAPITULO%.c"
)

:: Gerar arquivos RESOLVIDOS
for /L %%i in (1,1,25) do (
    if %%i LSS 10 (
        set "num=0%%i"
    ) else (
        set "num=%%i"
    )
    
    (
        echo //Atividade Resolvidos !num! - Capítulo %CAPITULO%
        echo #include ^<stdio.h^>
        echo.
        echo int main^(^)
        echo {
        echo.
        echo     return 0;
        echo }
    ) > "%PASTA_CAP%\Resolvidos\Res!num!_Cap%CAPITULO%.c"
)

echo.
echo ========================================
echo Arquivos criados com sucesso como "%PASTA_CAP%"
echo ========================================
echo.
echo.
pause
