# Infineon's OPTIGA&trade; Trust X on-chip DTLS example

## Description

This repository contains one of Application Notes for [OPTIGA™ Trust X](www.infineon.com/optiga-trust-x) security chip, showing how to perform a DTLS handshake with mutual authentication supported by on-chip DTLS 1.2 client feature of the OPTIGA™ Trust X (supported ciphersuite TLS_ECDHE_ECDSA_WITH_AES128_CCM_8). On-chip DTLS implementation means, that the host MCU implements DTLS Record [Layer](https://tools.ietf.org/html/rfc6347#section-4.1)  (part of the core hotscode [library](https://github.com/Infineon/optiga-trust-x/tree/master/optiga/dtls)), as well as data reassembly and fragmentation (if required).

* **You can find step-by-step get started guide on the [Wiki page](https://github.com/Infineon/onchipdtls-optiga-trust-x/wiki) of the project**
* You can find more information about the security chip in the core [repository](https://github.com/Infineon/optiga-trust-x)
* You can find other Application Notes in the respective [repository](https://github.com/Infineon/appnotes-optiga-trust-x)

## Summary
In this guide you may find the following steps:
* How to import this project into the DAVE™ IDE
* How to build the software and flash the development board (described below)
* How to setup a local Ethernet network for this example
* How to start a sample OpenSSL DTLS 1.2 server and connect the evaluation kit running DTLS 1.2 client
* How to debug and perform the project

## Hardware and Software
<p align="center">
  <img src="https://www.infineon.com/export/sites/default/_images/product/evaluation-boards/OPTIGA-trust-x-eval-kit.jpg_123076721.jpg">
</p>

* This get started guide uses the [OPTIGA™ Trust X evaluation and demonstration kit](https://www.infineon.com/cms/en/product/evaluation-boards/optiga-trust-x-eval-kit/)
* This get started guide uses DAVE™ IDE as a reference software development platform
* You need a Windows OS in order to follow this guide

## Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
