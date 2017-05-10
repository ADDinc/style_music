#include "essentaisAlgoritms.hpp"

Pool getPoolMetadataReader(const string audioFilename)
{
    Algorithm *metadata = AlgorithmFactory::create("MetadataReader",
                                                   "filename", audioFilename,
                                                   "failOnError", true,
                                                   "tagPoolName", "metadata.tags",
                                                   "filterMetadata", false);
    string title, artist, album, comment, genre, tracknumber, date;
    int duration, sampleRate, bitrate, channels;

    Pool poolTags;
    metadata->output("title").set(title);
    metadata->output("artist").set(artist);
    metadata->output("album").set(album);
    metadata->output("comment").set(comment);
    metadata->output("genre").set(genre);
    metadata->output("tracknumber").set(tracknumber);
    metadata->output("date").set(date);

    metadata->output("bitrate").set(bitrate);
    metadata->output("channels").set(channels);
    metadata->output("duration").set(duration);
    metadata->output("sampleRate").set(sampleRate);

    metadata->output("tagPool").set(poolTags);

    metadata->compute();

    delete metadata;

    return poolTags;
}

MapTags getMapMetadataReader(Pool metaPool)
{
    return metaPool.getStringPool();
};

Pool getPoolMonoLoader(const string audioFilename)
{

    Pool pool;

    int sampleRate = 44100;
    int frameSize = 2048;
    int hopSize = 1024;

    AlgorithmFactory &factory = standard::AlgorithmFactory::instance();
    Algorithm *audio = factory.create("MonoLoader",
                                      "filename", audioFilename,
                                      "sampleRate", sampleRate);

    Algorithm *fc = factory.create("FrameCutter",
                                   "frameSize", frameSize,
                                   "hopSize", hopSize);

    Algorithm *w = factory.create("Windowing",
                                  "type", "blackmanharris62");

    Algorithm *spec = factory.create("Spectrum");
    Algorithm *mfcc = factory.create("MFCC");

    /////////// CONNECTING THE ALGORITHMS ////////////////

    // Audio -> FrameCutter
    vector <Real> audioBuffer;

    audio->output("audio").set(audioBuffer);
    fc->input("signal").set(audioBuffer);

    // FrameCutter -> Windowing -> Spectrum
    vector <Real> frame, windowedFrame;

    fc->output("frame").set(frame);
    w->input("frame").set(frame);

    w->output("frame").set(windowedFrame);
    spec->input("frame").set(windowedFrame);

    // Spectrum -> MFCC
    vector <Real> spectrum, mfccCoeffs, mfccBands;

    spec->output("spectrum").set(spectrum);
    mfcc->input("spectrum").set(spectrum);

    mfcc->output("bands").set(mfccBands);
    mfcc->output("mfcc").set(mfccCoeffs);



    /////////// STARTING THE ALGORITHMS //////////////////
    statusMsg("-------- start processing " + audioFilename + " --------");

    audio->compute();

    while (true) {

        // compute a frame
        fc->compute();

        // if it was the last one (ie: it was empty), then we're done.
        if (!frame.size()) {
            break;
        }

        // if the frame is silent, just drop it and go on processing
        if (isSilent(frame)) continue;

        w->compute();
        spec->compute();
        mfcc->compute();

        pool.add("lowlevel.mfcc", mfccCoeffs);

    }

    // aggregate the results
    Pool aggrPool; // the pool with the aggregated MFCC values
    const char *stats[] = {"mean", "var", "median", "min", "max", "dmean", "dmean2", "dvar", "dvar2"};

    Algorithm *aggr = AlgorithmFactory::create("PoolAggregator",
                                               "defaultStats", arrayToVector<string>(stats));

    aggr->input("input").set(pool);
    aggr->output("output").set(aggrPool);
    aggr->compute();

    delete audio;
    delete fc;
    delete w;
    delete spec;
    delete mfcc;
    delete aggr;

    return aggrPool;
}

MapMono getMapMonoLoader(Pool monoPool)
{
    return monoPool.getRealPool();
};

void YamlOutputPool(const string outputFilename, Pool pool)
{
    Algorithm *output = AlgorithmFactory::create("YamlOutput",
                                                 "filename", outputFilename);
    output->input("pool").set(pool);
    output->compute();
    delete output;
}
