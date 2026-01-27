from setuptools import find_packages
from setuptools import setup

setup(
    name='go2_inter',
    version='0.0.0',
    packages=find_packages(
        include=('go2_inter', 'go2_inter.*')),
)
