from setuptools import setup, find_packages

setup(name='pycgal',
      version='0.0.1',
      description='cgal python-binding library.',
      url='https://github.com/chengaoyu/cgal-swig-bindings',
      author='Chen Gaoyu',
      author_email='chengaoyu2013@gmail.com',
      # namespace_packages=['pymi'],
      packages=find_packages('src'),
      package_dir={'': 'src'},
      package_data = {
            'CGAL':['*.so']
      },
      scripts=[],
      zip_safe=False)