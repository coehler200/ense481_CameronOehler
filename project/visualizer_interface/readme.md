# Cube Visualizer Interface

A simple Python flask server that connects to the STM32 board over serial and 
on GET returns roll, pitch, and heading data.

## Install
Enter the python environment you wish to install and run with. \
Run: `pip install -r requirements.txt` or `python -m pip install -r requirements.txt`

## Run
Set `COM_PORT` to the port the STM32 is on. \
Run: `python main.py` \
Exit with Ctrl+C