# Critical plane

Fatigue analyses using critical plane methods, to apply on stress histories obtained e.g. from finite element methods.

**Warning:** Work in progress, use at own risk. 

This library is a simplified version of code used in paper [https://doi.org/10.1016/j.ijfatigue.2019.105448](https://doi.org/10.1016/j.ijfatigue.2019.105448).

## TODO
- [ ] Implement more efficient adaptive scheme (e.g. Quadtree lookup)
- [ ] Fix multithreaded version
- [ ] Improve test coverage
- [ ] Add benchmarks
- [ ] Separate library from CLI
- [ ] Constexpr search space generation for cache-aligned data structure
- [ ] Implement Smith-Watson-Topper criterion 
- [ ] Implement DangVan criterion


## Cite

If appropriate, please considering citing the following paper

    @article{Sunde2019,
        title = {Efficient implementation of critical plane for 3D stress histories using triangular elements},
        journal = {International Journal of Fatigue},
        volume = {134},
        pages = {105448},
        year = {2020},
        issn = {0142-1123},
        doi = {https://doi.org/10.1016/j.ijfatigue.2019.105448},
        url = {https://www.sciencedirect.com/science/article/pii/S0142112319305523},
        author = {Steffen Loen Sunde and Filippo Berto and Bjørn Haugen},
        keywords = {Critical plane, Multiaxial fatigue, Computation, Findley criterion, Fatigue crack initiation},
    }


## Licence

GPL?