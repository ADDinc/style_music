ALG_INCLUDE = --include-algos=MetadataReader,AudioLoader,Resample,MonoLoader,MonoMixer,FrameCutter,Windowing,Magnitude,FFT,Spectrum,DCT,TriangularBands,MelBands,MFCC,PoolAggregator

all:
	./waf configure --mode=release --prefix=../../bin $(ALG_INCLUDE)
	./waf
	./waf install