[![Download Latest Release](https://img.shields.io/github/v/release/Sagatt/IGI2NeonixPatch?display_name=release&label=Download%20Latest%20Release&color=21ABC7)](https://github.com/Sagatt/IGI2NeonixPatch/releases) [![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]
[![LOGO](https://staticdelivery.nexusmods.com/mods/5664/images/8/8-1726626244-2078707165.png)](#)

## IGI 2: Neonix Patch

The IGI 2: Neonix Patch is a work-in-progress patch designed to address various gameplay issues and errors found in IGI 2: Covert Strike (version 1.3). This patch focuses on enhancing the overall gameplay experience, fixing several long-standing bugs, and improving the game’s performance and compatibility with modern systems.

### Discord:
[Neonix Modding Team Discord Server](https://discord.gg/GdXMbbVUcE).

- If there is some issue/request just open new issue and fill out the predefined template.

## Installation
1. Download the release build of [IGI 2: Neonix Patch](https://github.com/Sagatt/IGI2NeonixPatch/releases) or the full version at [Nexusmods](https://www.nexusmods.com/igi2covertstrike/mods/8) .
2. Open the downloaded ZIP file in archive software like WinRar/7-Zip.
3. Extract all files inside the ZIP file to the game folder.


## Known Issues
- When alt-tabbing and coming back to the game you might experience a slightly sped up gun animation for a few seconds.

## INI Settings
- All these options are configurable in 'settings.ini'. The file is automatically created when launching game for the first time with the patch otherwise you can create it manually.
- Most options are configurable in game options.
```ini
[IGI2]
Windowed=1         ; Set game to borderless mode
SkipIntroScreens=0 ; Skips intro-screens of the game

[Camera]
FirstpersonFOV=100 ; Alters the FOV of the firstperson mode
ThirdpersonFOV=100 ; Alters the FOV of the thirdperson mode
FixThirdperson=0   ; Inverts third-person mouse movement
```

## List of Patches
### Additions:
- **HD Textures:** High definition and properly color-corrected character textures and loading screens.
- **Custom FOV Adjustment:** Allows players to customize their field of view (FOV) for better gameplay perspective.
- **More accurate sensitivity slider:** Adds a bigger sensitivity mouse slider sensitivity onto the game for better accuracy. 

### Fixes:
- **Weapon Correct FPS Animations:** Restores accurate frames per second for the animations providing a smoother weapon handling.
- **Mission Restart Camera Fix:** Fixes the broken camera when restarting missions or interacting with map computers.
- **Mouse and Input Fixes:** Fixes input-related issues when moving the mouse or alt-tabbing while pausing the game.
- **Alt-Key Bug:** Fixes the bug where the Alt key remains held after alt-tabbing, causing unintended toggling of fullscreen when pressing Enter.
- **Pause Menu Camera Shake Fix:** Removes the annoying camera shaking when pausing the game.
- **Windowed Mode Mouse Cursor Fix:** Restores proper mouse cursor functionality in windowed mode.
- **Improved Character Movement:** Removes the clunky and rigid movement, making character control smoother and more similar to the original IGI 1.
- **Fixed Mouse Inversion & Wrong Speed:** Fixes the mouse being inverted and incorrect mouse speed.
- **Fixed Objects Stuttering While Game Is Paused:** Resolves object stuttering when pausing the game.
- **Fixed Weapon Animations While Game Is Paused:** Corrects weapon animations still playing when the game is paused.
- **Fixed Thermal Vision in Cutscenes:** Ensures thermal vision is not enabled in cutscenes when it shouldn't be.
- **Fixed SPAS-12 Walk and Run Animations:** Corrects the walking and running animations for the SPAS-12 shotgun.
- **Flickering in Cutscenes:** Fixed flickering objects/npcs in cutscenes.

### Improvements:
- **Borderless Windowed Mode:** Changes windowed style to borderless mode for better performance and proper rendering over the taskbar.

### Work in Progress:
- **World Interaction FPS Fix:** Ensures correct frame rate when interacting with objects in the world (e.g., dropping weapons, interacting with doors, cutscenes).
- **Main Menu Lag:** Working on reducing lag in the main menu.
- **Weapon Sound Delay After Grenade Explosion:** After throwing and exploding a grenade, switching to another weapon causes a delay in weapon firing sound for a few seconds. Fix in progress.
- **Map Fixes:** Correcting various issues with the original game maps and recalculating their lightmaps.
- **Weapon Laser Lag:** Fixing lag in weapon laser behavior.
- **Gun Animation Freeze:** Fixing the issue where holding right-click freezes the gun animation.

> [!NOTE]  
> If you're using a non-v1.3 game executable, the patch may not work correctly. Ensure you have the correct version of the game for full functionality.

## CC Attribution-NonCommercial-NoDerivs 4.0 International

To add a CC BY-NC-ND License to your project, just add the following to your
`README.md`. You should also copy the corresponding [license text
file](LICENSE-CC-BY-NC-ND) and rename it to `LICENSE`.

```markdown
Shield: [![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-NoDerivs 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: http://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg
```
Shield: [![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-NoDerivs 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: http://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg
