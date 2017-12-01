1. Copy testiboot folder to the roms folder
2. Open /etc/emulationstation/es_systems.cfg file
3. Add next script between last two row

```
<system>
	<name>testi</name>
	<fullname>Testi</fullname>
	<path>/home/pi/RetroPie/roms/testiboot</path>
	<extension>.sh</extension>
	<command>sudo /home/pi/RetroPie/testibootti/testibootteri.sh 0 _SYS_ zxspectrum %ROM%</command>
	<platform>zxspectrum</platform>
	<theme>zxspectrum</theme>
</system>

```

4. Restart system
