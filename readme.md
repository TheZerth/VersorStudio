
<!-- ABOUT THE PROJECT -->
## About The Project

Welcome to the GitHub of VersorStudio, a sandbox environment built for the analysis of mathematics and physics.
Specifically aimed at the study of geometric algebra and its applications in physics, this project is a work in progress and will be updated as time goes on.

Versor Studio is equipped with a GUI allowing you to create and manipulate geometric objects representative of things such as angular momentum or the magnetic field. These objects may then be manipulated to solve for a variety of unknowns.
A future hope is to implement a basic 3D modeling function for simple shapes to allow for the visualization of Maxwell's equations and their interaction with objects and situations such as a two wire transmission or a plate capacitor.

Currently only the foundation of the GA mathematics is in place as well as a basic GUI for the manipulation of 2d orthographic space. The foundation of the GA math system itself is unit-of-measure/space agnostic however for brevity and simplicity the current implementation is in 2d Euclidean space, constructed with orthogonal basis vectors e1 and e2.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

GLFW, GLAD, ImGui, ImPlot, CMake, VCPKG, C++

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

To use this project, you will need to clone the repository and build the project using CMake. The project is built using CMake and VCPKG, so you will need to have these installed on your system. 
The project is fully crossplatform and will work on Windows, MacOS, and Linux. Windows users must ise the Visual Studio compiler, MacOS users must use the Clang compiler, and Linux users must use the GCC compiler.

### Installation 

To be added

1. Exmaple
2. Clone the repo
   ```sh
   git clone https://github.com/TheZerth/VersorStudio.git
   ```
3. Install CMake
   ```sh
   sudo apt install cmake
   ```
4. Install vcpkg
   ```sh
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg; .\bootstrap-vcpkg.sh
   ```
   ```In IDE CMake Settings add the following line to the CMake options:
    -DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

To be added

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Add basic 2d solution functions, intersection, magnitude, projection, etc. 
- [ ] Add basic 2d transformation functions, rotation, translation, scaling, mirroring, etc.
- [ ] Add Google Test for unit testing of the GA math library, ensure axioms are met
- [ ] Add 2d magnetic field simulator using F_M = Q(v << B), with B field being a bivector instead of the traditional vector


See the [open issues](https://github.com/othneildrew/Best-README-Template/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

The Zerth - if you know, you know.

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Malven's Flexbox Cheatsheet](https://flexbox.malven.co/)
* [Malven's Grid Cheatsheet](https://grid.malven.co/)
* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Font Awesome](https://fontawesome.com)
* [React Icons](https://react-icons.github.io/react-icons/search)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 