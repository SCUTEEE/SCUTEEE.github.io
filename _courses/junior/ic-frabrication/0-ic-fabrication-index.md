---
layout: article
title: 集成电路制造技术
permalink: /courses/junior/ic-fabrication/index
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
mode: immersive
tags: 集成电路
key: 0-ic-fabrication-index
nav_key: courses
show_edit_on_github: false
show_date: false
sidebar:
  nav: ic-fabrication
aside:
  toc: true
header:
  theme: dark
article_header:
  type: overlay
  theme: dark
  background_color: '#ffffff'
  background_image:
    src: http://www.circuitstoday.com/wp-content/uploads/2010/07/nmos-ic-fabrication.jpg
    gradient: 'linear-gradient(0deg, rgba(0, 0, 0 , .5), rgba(0, 0, 0, .5))'
---

<!--more-->

# How Intel Makes Chips

> source: [https://www.intel.com/content/www/us/en/history/museum-transistors-to-transformations-brochure.html](https://www.intel.com/content/www/us/en/history/museum-transistors-to-transformations-brochure.html)

## Sand to Ingot

`Sand`{:.info} Sand has a high percentage of silicon—the starting material for computer chips. Silicon is a semiconductor, meaning that it can be turned into an excellent conductor or insulator of electricity with minor amounts of impurities added.

`Melted Silicon`{:.info} Silicon is purified to less than one alien atom per billion. It is melted and cooled into a solid crystal lattice cylinder, called an ingot.

`Monocrystalline Silicon Ingot`{:.info} The silicon ingot has a diameter of 300 millimeters (mm) and weighs about 100 kilograms (kg).

## Ingot to Wafer

`Slicing Ingots`{:.info} The ingot is cut into individual silicon discs called wafers. Each wafer is about one mm thick.

`Polishing Wafers`{:.info} The wafers are polished to a flawless, mirror-smooth surface. Intel buys these manufacturing-ready wafers.How Intel Makes Chips

## Photolithography

`Applying Photoresist`{:.info} Photolithography is a process that imprints a specific pattern on the wafer. It starts by applying a light-sensitive, etch-resistant material called photoresist onto the wafer surface. 

`Exposing Photoresist`{:.info} The photoresist is hardened and parts of it are exposed to ultraviolet light, making it soluble. The light passes through a mask (similar to a stencil), and then through a lens to shrink and print circuit patterns on each layer of every chip on the wafer.

`Developing Resist`{:.info} A chemical process removes the soluble photoresist, leaving a patterned photoresist image as determined by what was on the mask.

## Ion Implantation

`Implanting Ions`{:.info} Ions (positively or negatively charged atoms) are embedded beneath the surface of the wafer in regions not covered by photoresist. This alters the conductive properties of the silicon in selected locations. 

`Removing Photoresist`{:.info} After the ion implantation, the photoresist is removed, resulting in certain regions being doped with alien atoms (green in the image).

`The Transistor`{:.info} Although hundreds of chips are usually built on a single wafer, the next steps focus on a small piece of a chip—a transistor.

## Etching

`Etching`{:.info} To create a fin for a tri-gate transistor, Intel applies a hard mask material (blue in the image) using photolithography. Then a chemical is applied to etchaway unwanted silicon, leaving behind a fin with a layer of hard mask on top. 

`Removing Hard Mask`{:.info} The hard mask is chemically removed, leaving a tall, thin silicon fin that will contain the channel of a transistor.

## Temporary gate formation

`Creating a Gate Dielectric`{:.info} Photoresist is applied to portions of the transistor, and a thin silicon dioxide layer (red in the image) is created by inserting the wafer in an oxygen-filled tube-furnace. This layer becomes a temporary gate dielectric.

`Creating a Gate Electrode`{:.info} Using photolithography, a temporary layer of polycrystalline silicon (yellow in the image) is created. This becomes a temporary gate electrode.

`Insulating the Transistor`{:.info} In another oxidation step, a silicon dioxide layer is created over the entire wafer (transparent red in the image) to insulate the transistor from other elements.

## “Gate-Last” High-K/Metal Gate Formation

`Removing the Temporary Gate`{:.info} The temporary gate electrode and gate dielectric are etched away in preparation for forming the final gate. This procedure is called gate-last.

`Applying High-k Dielectric Material`{:.info} Multiple layers of high-k dielectric material(yellow in the image) are applied to the wafer surface using a method called atomic layer deposition. This material is etched away in some areas, such as the silicon dioxide layer.

`Forming a Metal Gate`{:.info} A metal gate electrode (blue in the image) is formed over the wafer and removed from regions other than the gate electrode. The combination of this and the high-k dielectric material improves performance and reduces leakage.

## Metal Deposition

`Preparing to Connect the Transistor`{:.info} Three holes are etched into the insulation layer (red in the image) above the transistor. The holes are filled with copper or another material that creates metal connections to other transistors.

`Electroplating`{:.info} The wafers are put into a copper sulphate solution. Copper ions are deposited onto the transistor using a process called electroplating. 

`After Electroplating`{:.info} Copper ions settle as a thin layer of copper on the transistor surface.

## Metal Layers

`Polishing`{:.info} The excess material is polished off, revealing a specific pattern of copper.

`Connecting with Metal Layers`{:.info} Like a multi-level highway, metal layers interconnect the transistors in a chip (middle and right images). The design of the chip determines how the connections are made. Although chips look flat, they can have more than 30 layers of this complex circuitry.

## Wafer Sort Test and Singulation

`Sort Testing`{:.info} After wafer processing is complete, each chip on a wafer is tested for its functionality.

`Slicing Wafers`{:.info} The wafer is cut into pieces called die.

`Moving to Packaging`{:.info} Based on the responses received in the wafersort test, die are selected for packaging.

## Packaging Die

`Individual Die`{:.info} The silicon die shown here is a 3rd generation Intel® Core™ processor, Intel’s first 22nm microprocessor using 3-D transistors.

`Packaging`{:.info} The substrate, the die, and a heat spreader are put together to form a completed processor. The green substrate creates the electrical and mechanical connections so that the processor can interact with the system. The silver-colored heat spreader is a thermal interface that helps dissipate heat.

`Completed Processor`{:.info} A completed processor, such as the 3rd generation Intel Core processor, is one of the most complex manufactured products on Earth.

## Class testing and Completed Processor

`Package Testing`{:.info} Processors undergo final testing for functionality, performance, and power.

`Binning`{:.info} Based on final test results, processors with the same capabilities are grouped into transporting trays.

`Retail Packaging`{:.info} Intel® processors, such as the 3rd generation Intel Core processor shown here, are sent to system manufacturers in trays, or they are boxed for retail stores.