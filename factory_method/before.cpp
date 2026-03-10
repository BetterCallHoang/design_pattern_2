  // SNAP code like this
  private SpeckleFilter createFilter() {

        switch (filter) {
            case BOXCAR_SPECKLE_FILTER:
                return new Boxcar(this, sourceProduct, targetProduct, filterSizeX, filterSizeY,
                        targetBandNameToSourceBandName);

            case MEDIAN_SPECKLE_FILTER:
                return new Median(this, sourceProduct, targetProduct, filterSizeX, filterSizeY,
                        targetBandNameToSourceBandName);

            case FROST_SPECKLE_FILTER:
                return new Frost(this, sourceProduct, targetProduct, filterSizeX, filterSizeY,
                        targetBandNameToSourceBandName, dampingFactor);

            case GAMMA_MAP_SPECKLE_FILTER:
                return new GammaMap(this, sourceProduct, targetProduct, filterSizeX, filterSizeY,
                        targetBandNameToSourceBandName, estimateENL, enl);

            case LEE_SPECKLE_FILTER:
                return new Lee(this, sourceProduct, targetProduct, filterSizeX, filterSizeY,
                        targetBandNameToSourceBandName, estimateENL, enl);

            case LEE_REFINED_FILTER:
                return new RefinedLee(this, sourceProduct, targetProduct, targetBandNameToSourceBandName);

            case LEE_SIGMA_FILTER:
                return new LeeSigma(this, sourceProduct, targetProduct, targetBandNameToSourceBandName,
                        numLooksStr, windowSize, targetWindowSizeStr, sigmaStr);

            case IDAN_FILTER:
                return new IDAN(this, sourceProduct, targetProduct, targetBandNameToSourceBandName,
                        numLooksStr, anSize);

            default:
                return null;
        }
    }

    
/**
 * Creates a dielectric model for soil moisture inversion.
 */
public class DielectricModelFactory {

    public static final String HALLIKAINEN = "Hallikainen";
    public static final String MIRONOV = "Mironov";

    public static DielectricModel createDielectricModel(final Operator op, final Product srcProduct,
                                                        final Product tgtProduct, final double invalidSMValue,
                                                        final double minSM, final double maxSM,
                                                        final Band smBand, final Band qualityIndexBand,
                                                        final String rdcBandName, final String modelName)
            throws OperatorException, IllegalArgumentException {

        switch (modelName) {

            case HALLIKAINEN:
                return new HallikainenDielectricModel(op, srcProduct, tgtProduct, invalidSMValue, minSM, maxSM, smBand, qualityIndexBand, rdcBandName);

            case MIRONOV:
                return new MironovDielectricModel(op, srcProduct, tgtProduct, invalidSMValue, minSM, maxSM, smBand, qualityIndexBand, rdcBandName);

            default:
                break;
        }

        return null;
    }
}


