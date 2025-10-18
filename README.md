# 3DByteNebula

# ElevenValueBoolean

**Author:** Cadell Richard Anderson  
**License:** Custom License: ElevenValueBoolean Attribution License (EAL) v1.0
**Version:** 0.2  
**Date:** July 2025


The simulation uses a set of initial conditions and physics-based rules (approximations of gravity, thermodynamics, nuclear forces, etc.). As it runs, it produces a continuous stream of complex, emergent data in the form of event logs to the console ([EVENT: DECAY], [EVENT: SYNTHESIS], [EVENT: ANNIHILATION], etc.). This output is a "bit stream" generated not randomly, but as a result of the simulated physical processes, including fusion. You've essentially created a virtual machine for producing physics-based information.

A Universe in a File: A Detailed Synopsis 🌌
This C++ program is a sophisticated, multi-scale universe simulator. It models cosmic phenomena on two distinct levels: the vast, galactic scale that you can see and navigate, and the invisible, quantum scale that is reported to you through text logs.

The Big Picture: The Cosmological Simulation (Macro Scale)
What you see on the screen is the macro-scale simulation. Think of it as a virtual petri dish for growing a galaxy.

The "Matter": The simulation starts with a cloud of 100,000 particles, which you can think of as representing gas and dust (initially hydrogen). Each particle has properties like position, velocity, temperature, and atomic number.

The "Physics": These particles aren't just floating randomly. They are influenced by a set of simplified but powerful physics rules:

A central gravitational pull causes them to orbit and clump together.

Thermodynamics and pressure gradients (hot, dense areas pushing outwards) create complex swirls and structures, mimicking the formation of nebulae and protostars.

Magnetohydrodynamics (MHD) applies magnetic forces, guiding the flow of ionized matter.

Stellar Nucleosynthesis: When particles in a region get extremely hot and dense, they "fuse," increasing their atomic number (e.g., hydrogen becomes helium, then carbon, etc.). In extreme cases, this triggers spectacular supernova and kilonova events, which forge and scatter even heavier elements.

The result is a dynamic, evolving simulation where you can witness the birth of galactic structures from a primordial cloud.

The Inner World: The Subatomic Simulation (Micro Scale) ⚛️
Running completely in the background is a second, parallel simulation. This one doesn't affect the big picture you see, but instead acts as a physics event logger.

The "Particles": This simulation contains a small number of fundamental particles: protons, neutrons, electrons, and positrons.

The "Forces": These particles interact based on highly simplified versions of the fundamental forces of nature:

Electromagnetism: Particles with like charges repel; opposites attract.

Strong Force (Approximation): An incredibly strong attraction binds protons and neutrons together at very short distances.

Weak Force (Approximation): This is modeled via a low-probability chance for a neutron to decay into a proton (beta decay).

The "Events": By simulating these interactions, the program logs key quantum and nuclear events as they happen, giving you a real-time feed of the universe's subatomic activity. This includes:

Deuterium Synthesis: A proton and neutron fusing to form a simple nucleus.

Beta Decay: A neutron changing into a proton.

Annihilation: An electron and its antimatter counterpart (a positron) meeting and turning into energy (gamma photons).

This micro-scale simulation is the source of your "fusion bit generator"—it's a constant stream of data about the fundamental events that, in a real universe, power the stars you see forming in the macro simulation.

Getting Started: Controls & Visuals 🎮
Here’s a quick guide on how to interact with your universe and understand what you're seeing.

Controls
Movement:

W / S: Move forward / backward.

A / D: Strafe left / right.

Spacebar / Left Ctrl: Move up / down.

View:

Left-Click + Drag Mouse: Look around / rotate the camera.

Mouse Scroll Wheel: Zoom in and out (adjusts Field of View).

Simulation Time:

= (Equals): Speed up time.

- (Minus): Slow down time.

0 (Zero): Reset time to normal speed (1.0x).

Hold Shift or Ctrl while adjusting time for finer or coarser control.

System:

R: Reset the entire simulation to its initial state.

Esc: Exit the program.

What You're Seeing on Screen
The Particles: Each dot is a "ByteParticle," representing a large collection of atoms.

Color = Element: The particle's color tells you what it's made of. The simulation uses a color scheme that roughly corresponds to the elements being formed:

White/Light Blue: Hydrogen (Atomic Number 1) & Helium (2)

Gray: Carbon (6)

Red: Oxygen (8)

Brown/Orange: Iron (26)

Purple/Gold: Heavy elements like Gold (79)

Dim Red Tint: A particle with a reddish, dimmer appearance is antimatter.

Redshift/Blueshift: Particles are tinted slightly blue if they are moving towards you and slightly red if they are moving away from you. This is the Doppler Effect overlay, a key concept in real-world astronomy.

The Flux Web: The faint blue lines that flicker between particles represent quantum entanglement. In this simulation, it's a visual effect showing a temporary, non-local connection between two particles. The brightness of the line indicates the strength (coherence) of the link, which fades over time, representing decoherence.
